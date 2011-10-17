#include "CrowdCalculator.h"

#include "graphics/OpenGL.h"

#include "Error.h"
#include "Exception.h"
#include "computation/OpenCL.h"
#include "Number.h"
#include "Random.h"
#include "String.h"


CrowdCalculator::CrowdCalculator(   const Logger*   logger,
                                    Profiler*       profiler,
                                    Display*        displayX11,
                                    GLXContext      contextGLX,
                                    const Settings* settings)
:   logger(logger),
    context(NULL),
    splatterer(NULL),
    workGroupsCalculator(NULL),
    workItemsCalculator(NULL),
    potentialCalculator(NULL),
    gradientCalculator(NULL),
    costCalculator(NULL),
    averageVelocityCalculator(NULL),
    speedCalculator(NULL),
    collisionResolver(NULL),
    agentMover(NULL),
    discomfortFile(settings->discomfortFile),
    exitFile(settings->exitFile),
    agentEntry0(settings->agentEntry0),
    agentEntry1(settings->agentEntry1),
    agentEntry2(settings->agentEntry2),
    agentEntry3(settings->agentEntry3),
    textureBufferDiscomfort(0),
    discomforts(NULL),
    basePotential(NULL),
    bufferSideLength(0),
    workGroupSideLength(settings->workGroupSideLength),
    elements(0),
    components(0),
    bytes(0),
    workGroupSize(settings->workGroupSideLength * settings->workGroupSideLength),
    agentCount(settings->agentCount),
    maximumRadius(settings->maximumRadius),
    totalBufferSize(0),
    isBreakingAfterOuterStep(false),
    isPotentialConverged(false),
    isFirstUpdate(true),
    isUsingGPU(settings->isUsingGPU),
    exitMode(AgentMover::EXIT_MODE_PARK)
{
    checkEntryArea(agentEntry0);
    checkEntryArea(agentEntry1);
    checkEntryArea(agentEntry2);
    checkEntryArea(agentEntry3);

    // This vector holds the agent counts, per group, and parked

    originalAgentCounts.resize(8, 0);


    //
    // Init OpenCL context (we can create shared resources after that)
    //

    initializeOpenCL(displayX11, contextGLX, settings->isProfilingQueue);

    initializeCalculators(profiler, settings->minimumRadius, settings->maximumRadius, settings->agentSeed);
}


CrowdCalculator::~CrowdCalculator()
{
    delete splatterer;

    delete workGroupsCalculator;
    delete workItemsCalculator;
    delete potentialCalculator;
    delete gradientCalculator;
    delete agentMover;
    delete costCalculator;
    delete averageVelocityCalculator;
    delete speedCalculator;

    delete collisionResolver;

    delete discomforts;

    delete context;

    clReleaseMemObject(basePotential);

    glDeleteBuffers(1, &textureBufferDiscomfort);
}


void CrowdCalculator::compute(ClientProfile* clientProfile, bool isProfiling, bool isResolvingCollisions, cl_float deltaTime)
{
    glDisable(GL_DEPTH_TEST);
    GL_ERROR;

    //
    // Splat all agent positions into density buffer and render all agents
    //

    if (isPotentialConverged || isFirstUpdate)
    {
        GL_PROFILE_CLIENT(isProfiling, clientProfile, writeDiscomfortTime, splatterer->prepareFramebuffer());

        GL_PROFILE_CLIENT(isProfiling, clientProfile, splatTime, splatterer->splat(agentMover->getCount(),
                                                                                   agentMover->getPositions(),
                                                                                   agentMover->getDirections(),
                                                                                   agentMover->getSpeeds(),
                                                                                   agentMover->getIds(),
                                                                                   agentMover->getRadii()));

        //
        // Retrieve splatted densities, velocities
        //

        GL_PROFILE_CLIENT(isProfiling, clientProfile, readSplatBuffersTime, splatterer->copyDataFromFramebuffer());

        glFinish();

        //
        // Compute average velocity for all agents
        //

        CL_PROFILE_CLIENT(isProfiling, clientProfile, computeAverageVelocityTime, context->queue,
                          averageVelocityCalculator->compute(isProfiling, splatterer->getDensitiesDiscomfortsVelocitiesShared()));

        //
        // Compute anisotropic speed field for all agents
        //

        CL_PROFILE_CLIENT(isProfiling, clientProfile, computeSpeedTime, context->queue,
                          speedCalculator->compute(isProfiling, splatterer->getDensitiesDiscomfortsVelocitiesShared()));

        //
        // Compute cost for agent groups
        //

        CL_PROFILE_CLIENT(isProfiling, clientProfile, computeCostTime, context->queue,
                          costCalculator->compute(isProfiling, speedCalculator->getSpeedsShared(), splatterer->getDensitiesDiscomfortsVelocitiesShared()));

    }

    //
    // Compute potential from cost for agent groups
    //

    CL_PROFILE_CLIENT(isProfiling, clientProfile, computePotentialTime, context->queue,
                      isPotentialConverged = potentialCalculator->compute(isProfiling, costCalculator->getCostsShared()));


    //
    // Compute gradient from potential for agent groups
    //

    // If potential is converged or if we want to visualize steps

    if (isPotentialConverged || isBreakingAfterOuterStep)
    {
        CL_PROFILE_CLIENT(isProfiling, clientProfile, computeGradientTime, context->queue,
                          gradientCalculator->compute(isProfiling, potentialCalculator->getPotentialsShared()));
    }

    if (isPotentialConverged)
    {
        //
        // Update all agent positions and velocity and write position hash
        //

        CL_PROFILE_CLIENT(isProfiling, clientProfile, moveAgentsTime, context->queue,
                          agentMover->compute(  isProfiling,
                                                gradientCalculator->getGradients01Shared(),
                                                gradientCalculator->getGradients23Shared(),
                                                speedCalculator->getSpeedsShared(),
                                                deltaTime,
                                                exitMode,
                                                potentialCalculator->getPotentialsShared()));

        if (isResolvingCollisions)
        {
            //
            // Detect and resolve agent collisions
            //

            CL_PROFILE_CLIENT(isProfiling, clientProfile, resolveCollisionsTime, context->queue,
                              collisionResolver->compute(isProfiling,
                                                         agentMover->getPositionsShared(),
                                                         agentMover->getRadiiShared(),
                                                         agentMover->getIdsShared(),
                                                         maximumRadius,
                                                         potentialCalculator->getPotentialsShared()));
        }
    }

    // Make sure everything is done so that we can render later

    clFinish(context->queue);

    isFirstUpdate = false;
}


void CrowdCalculator::initializeOpenCL(Display* displayX11, GLXContext contextGLX, bool isProfilingQueue)
{
    cl_int status;

    cl_uint platformCount;

    CL_ERROR( clGetPlatformIDs(0, NULL, &platformCount) );

    std::vector<cl_platform_id> platforms(platformCount);

    CL_ERROR( clGetPlatformIDs(platformCount, &platforms.at(0), NULL) );

    //
    // Create context
    //

    cl_context_properties properties[7] = { CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties> (platforms[0]),
                                            CL_GL_CONTEXT_KHR,   reinterpret_cast<cl_context_properties> (contextGLX),
                                            CL_GLX_DISPLAY_KHR,  reinterpret_cast<cl_context_properties> (displayX11),
                                            0};


    cl_context clContext;

    if (isUsingGPU)
    {
        clContext = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &status);
        logger->logInfo("OpenCL - Requesting GPU device context.");
    }
    else
    {
        clContext = clCreateContextFromType(properties, CL_DEVICE_TYPE_CPU, NULL, NULL, &status);
        logger->logInfo("OpenCL - Requesting CPU device context.");
    }

    CL_ERROR(status);



    // Get devices

    size_t size;

    CL_ERROR( clGetContextInfo(clContext, CL_CONTEXT_DEVICES, 0, NULL, &size) );
    size_t count = size / sizeof(cl_device_id);
    std::vector<cl_device_id> deviceIds(count);
    CL_ERROR( clGetContextInfo(clContext, CL_CONTEXT_DEVICES, size, &deviceIds.at(0), &size) );

//  clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1,

    cl_device_id device = deviceIds.at(0);

    CL_ERROR( clGetDeviceInfo(device, CL_DRIVER_VERSION, 0, NULL, &size) );

    cl_device_type deviceType;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &deviceType, NULL) );

    if (isUsingGPU)
    {
        if (deviceType == CL_DEVICE_TYPE_GPU)
        {
            logger->logInfo("OpenCL - Confirmed that device type is GPU.");
        }
        else
        {
            throw Exception("Wrong OpenCL device type!");
        }
    }
    else
    {
        if (deviceType == CL_DEVICE_TYPE_CPU)
        {
            logger->logInfo("OpenCL - Confirmed that device type is CPU.");
        }
        else
        {
            throw Exception("Wrong OpenCL device type!");
        }
    }

    std::vector<char> driverName(size);
    CL_ERROR( clGetDeviceInfo(device, CL_DRIVER_VERSION, size, &driverName.at(0), NULL) );
    logger->logInfo("OpenCL - Driver version: " + QString(&driverName.at(0)));

    cl_ulong maxMemAllocSize;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &maxMemAllocSize, NULL) );
    logger->logInfo("OpenCL - CL_DEVICE_MAX_MEM_ALLOC_SIZE: " + QString::number(maxMemAllocSize / 1024 / 1024) + " MB");

    cl_ulong deviceGlobalMemSize;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &deviceGlobalMemSize, NULL) );
    logger->logInfo("OpenCL - CL_DEVICE_GLOBAL_MEM_SIZE: " + QString::number(deviceGlobalMemSize / 1024 / 1024) + " MB");

    cl_ulong deviceLocalMemSize;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &deviceLocalMemSize, NULL) );
    logger->logInfo("OpenCL - CL_DEVICE_LOCAL_MEM_SIZE: " + QString::number(deviceLocalMemSize / 1024 ) + " kB");

    cl_device_fp_config floatConfig;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_SINGLE_FP_CONFIG , sizeof(cl_device_fp_config), &floatConfig, NULL) );
    bool isSupportingRoundToInf = floatConfig & CL_FP_ROUND_TO_INF;

    if (!isSupportingRoundToInf)
    {
        throw Exception("OpenCL device does not support round to infinity which is required for ceil and floor!");
    }

    cl_bool isImageSupported;
    CL_ERROR( clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(isImageSupported), &isImageSupported, NULL) );

    if (!isImageSupported)
    {
        throw Exception("OpenCL device does not support images!");
    }

    cl_uint imageFormatCount;
    CL_ERROR( clGetSupportedImageFormats(clContext, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D, 0, NULL, &imageFormatCount) );

    std::vector<cl_image_format> imageFormats;
    imageFormats.resize(imageFormatCount);
    CL_ERROR( clGetSupportedImageFormats(clContext, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D, imageFormatCount, &imageFormats[0], NULL) );

    std::vector<cl_image_format>::const_iterator iterator;
    bool isSupportingFloatImage = false;

    for (iterator = imageFormats.begin(); iterator != imageFormats.end(); ++iterator)
    {
        if ( ((*iterator).image_channel_data_type == CL_FLOAT) && ((*iterator).image_channel_order == CL_RGBA))
        {
            isSupportingFloatImage = true;

            break;
        }
    }

    if (!isSupportingFloatImage)
    {
        throw Exception("OpenCL context does not support RGBA float images!");
    }

    // Create queue

    cl_command_queue queue;

    if (isProfilingQueue)
    {
        queue = clCreateCommandQueue(clContext, device, CL_QUEUE_PROFILING_ENABLE, &status);
        logger->logInfo("OpenCL - Configuration uses queue profiling.");
    }
    else
    {
        queue = clCreateCommandQueue(clContext, device, 0, &status);
        logger->logInfo("OpenCL - Configuration does not use queue profiling. Kernel times output will be disabled.");
    }

    CL_ERROR(status);

    context = new Context(clContext, device, queue);
}


void CrowdCalculator::initializeCalculators(Profiler* profiler, cl_float minimumRadius, cl_float maximumRadius, int agentSeed)
{
    // Load base discomfort image containing walls and initialize size variables

    loadDiscomfortImage(discomfortFile, &textureBufferDiscomfort, &discomforts);

    splatterer = new Splatterer(logger, context, bufferSideLength, "textures/agent.png", discomforts);

    //
    // Compute checkered textures through OpenCL to verify the position of work groups and items
    //

    workGroupsCalculator = new WorkGroupCalculator( logger,
                                                    profiler,
                                                    context,
                                                    elements,
                                                    workGroupSize,
                                                    bufferSideLength,
                                                    bufferSideLength * bufferSideLength * sizeof(cl_float),
                                                    workGroupSideLength);
    workGroupsCalculator->compute();

    workItemsCalculator = new WorkItemCalculator(   logger,
                                                    profiler,
                                                    context,
                                                    elements,
                                                    workGroupSize,
                                                    bufferSideLength,
                                                    bufferSideLength * bufferSideLength * sizeof(cl_float),
                                                    workGroupSideLength);
    workItemsCalculator->compute();

    averageVelocityCalculator = new AverageVelocityCalculator(  logger,
                                                                profiler,
                                                                context,
                                                                elements,
                                                                workGroupSize,
                                                                bufferSideLength,
                                                                bytes);
    speedCalculator = new SpeedCalculator(logger, profiler, context, elements, workGroupSize, bufferSideLength, bytes);
    costCalculator = new CostCalculator(logger, profiler, context, elements, workGroupSize, bufferSideLength, bytes);

    // Create base potential from exit locations

    basePotential = loadExitImage(exitFile);

    potentialCalculator = new PotentialCalculator(  logger,
                                                    profiler,
                                                    context,
                                                    elements,
                                                    workGroupSize,
                                                    bufferSideLength,
                                                    bytes,
                                                    basePotential,
                                                    workGroupSideLength);

    gradientCalculator  = new GradientCalculator(logger, profiler, context, elements, workGroupSize, bufferSideLength, bytes);

    originalAgents = initializeAgents(minimumRadius, maximumRadius, agentSeed);

    agentMover = new AgentMover(context,
                                profiler,
                                workGroupSize,
                                bufferSideLength,
                                agentCount,
                                bufferSideLength,
                                agentEntry0,
                                agentEntry1,
                                agentEntry2,
                                agentEntry3,
                                originalAgentCounts);

    agentMover->setAgents(originalAgents);

    collisionResolver = new CollisionResolver(context, profiler, workGroupSize, agentCount, bufferSideLength);

    logger->logInfo("Using " + QString::number(agentCount) + " agents" );


    clUnloadCompiler();
}


std::vector<Agent> CrowdCalculator::initializeAgents(cl_float minimumRadius, cl_float maximumRadius, int agentSeed)
{
    if (minimumRadius <= 0.0f)
    {
        throw Exception("Minimum radius is less or equal zero!");
    }

    if (minimumRadius > maximumRadius)
    {
        throw Exception("Minimum radius is greater than maximum radius!");
    }

    // Seed random number generator based on whether configuration seed is negative

    if (agentSeed < 0)
    {
        uint seed = time(NULL);
        srandom( seed );
        logger->logInfo("Using time (" + QString::number(seed) + ") as seed.");
    }
    else
    {
        uint seed = static_cast<uint> (agentSeed);
        srandom( seed );
        logger->logInfo("Using " + QString::number(seed) + " as seed.");
    }

    std::vector<Agent> agents;

    for (uint i = 0; i < agentCount; i++)
    {
        // Maximum speed is 12

        float speed = 4.0f + Random::randomFloat() * 8.0f;

        Agent agent;

        agent.position.x    = 5.0f + Random::randomFloat() * (bufferSideLength - 10.0f);
        agent.position.y    = 5.0f + Random::randomFloat() * (bufferSideLength - 10.0f);
        agent.direction.x   = 1.0f;
        agent.direction.y   = 0.0f;
        agent.speed         = speed;
        agent.maximumSpeed  = speed;
        agent.radius        = minimumRadius + Random::randomFloat() * (maximumRadius - minimumRadius);

        if (i < agentCount * 0.25f)
        {
            agent.id        = 0;
        }
        else if (i < agentCount * 0.5f)
        {
            agent.id        = 1;
        }
        else if (i < agentCount * 0.75f)
        {
            agent.id        = 2;
        }
        else
        {
            agent.id        = 3;
        }

        // Increment agent count for that group

        originalAgentCounts[agent.id]++;

        agent.turnRate      = 0.15f;  // 0.5 is too high  0.05 too low

        agents.push_back(agent);
    }


    return agents;
}


void CrowdCalculator::loadDiscomfortImage(QString            filename,
                                          GLuint*            textureBufferDiscomfort,
                                          BufferTexture**    sharedTextureBufferDiscomfortTexture)
{
    try
    {
        QImage image = Texture::loadTexture(filename, false, true);

        if ( image.width() != image.height() )
        {
            throw Exception("Discomfort image is not square!");
        }

        bufferSideLength = static_cast<size_t> (image.width());

        if (!Number::isPowerOfTwo(bufferSideLength))
        {
            throw Exception("Discomfort image dimension is not a power of two!");
        }

        elements        = bufferSideLength * bufferSideLength;
        components      = elements * 4;
        bytes           = components * sizeof(cl_float);


        std::vector<float> data(components);

        Texture::convertToFloats(image, data, elements);

        glGenBuffers(1, textureBufferDiscomfort);
        GL_ERROR;

        glBindBuffer(GL_TEXTURE_BUFFER, *textureBufferDiscomfort);
        GL_ERROR;

        glBufferData(GL_TEXTURE_BUFFER, bytes, &data[0], GL_STATIC_DRAW);
        GL_ERROR;
        totalBufferSize += bytes;

        //
        // Create texture
        //

        *sharedTextureBufferDiscomfortTexture = new BufferTexture();

        (*sharedTextureBufferDiscomfortTexture)->attachToBufferObject(*textureBufferDiscomfort);


        logger->logInfo("Loaded \"" + filename + "\" as discomfort map");
    }
    catch (Exception& e)
    {
        throw Exception("Could not load discomfort map: " + e.message);
    }
}


cl_mem CrowdCalculator::loadExitImage(QString filename)
{
    try
    {
        QImage image = Texture::loadTexture(filename, false, true);

        if ( image.width() != image.height() )
        {
            throw Exception("Exit image is not square!");
        }

        if (!Number::isPowerOfTwo(static_cast<size_t> (image.width())))
        {
            throw Exception("Exit image dimension is not a power of two!");
        }

        if (static_cast<size_t> (image.width()) != bufferSideLength)
        {
            throw Exception("Exit image dimension does not match discomfort image dimension!");
        }

        std::vector<float> data(components);

        Texture::convertToFloats(image, data, elements);


        // Convert non-zero elements to infinity

        std::vector<float>::iterator iterator;

        for (iterator = data.begin(); iterator != data.end(); ++iterator)
        {
            if ((*iterator) > 0.0f)
            {
                (*iterator) = INFINITY;
            }
        }


        cl_int status;

        // Request read only because this is only copied from

        cl_mem buffer = clCreateBuffer(context->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, &data[0], &status);
        CL_ERROR(status);

        totalBufferSize += bytes;

        logger->logInfo("Loaded \"" + filename + "\" as exit map");

        return buffer;
    }
    catch (Exception& e)
    {
        throw Exception("Could not load exit map: " + e.message);
    }
}

/*
cl_mem CrowdCalculator::createExits(Vector4i exit0, Vector4i exit1, Vector4i exit2, Vector4i exit3)
{
    int maximum = bufferSideLength - 1;

    // Initialize buffer of infinities

    std::vector<float> data(components, INFINITY);

    exit0.z = NumberTemplate<int>::clamp(exit0.x, maximum, exit0.z);
    exit0.w = NumberTemplate<int>::clamp(exit0.y, maximum, exit0.w);

    // Write exit0 into buffer

    for (int x = exit0.x; x <= exit0.z; x++)
    {
        for (int y = exit0.y; y <= exit0.w; y++)
        {
            data[ Number::indexFromPosition(x, y, bufferSideLength, 4) + 0 ] = 0.0f;
        }
    }

    exit1.z = NumberTemplate<int>::clamp(exit1.x, maximum, exit1.z);
    exit1.w = NumberTemplate<int>::clamp(exit1.y, maximum, exit1.w);

    // Write exit1 into buffer

    for (int x = exit1.x; x <= exit1.z; x++)
    {
        for (int y = exit1.y; y <= exit1.w; y++)
        {
            data[ Number::indexFromPosition(x, y, bufferSideLength, 4) + 1 ] = 0.0f;
        }
    }

    exit2.z = NumberTemplate<int>::clamp(exit2.x, maximum, exit2.z);
    exit2.w = NumberTemplate<int>::clamp(exit2.y, maximum, exit2.w);

    // Write exit2 into buffer

    for (int x = exit2.x; x <= exit2.z; x++)
    {
        for (int y = exit2.y; y <= exit2.w; y++)
        {
            data[ Number::indexFromPosition(x, y, bufferSideLength, 4) + 2 ] = 0.0f;
        }
    }

    exit3.z = NumberTemplate<int>::clamp(exit3.x, maximum, exit3.z);
    exit3.w = NumberTemplate<int>::clamp(exit3.y, maximum, exit3.w);

    // Write exit3 into buffer

    for (int x = exit3.x; x <= exit3.z; x++)
    {
        for (int y = exit3.y; y <= exit3.w; y++)
        {
            data[ Number::indexFromPosition(x, y, bufferSideLength, 4) + 3 ] = 0.0f;
        }
    }

    cl_int status;

    // Request read only because this is only copied from

    cl_mem buffer = clCreateBuffer(context->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, &data[0], &status);
    CL_ERROR(status);

    totalBufferSize += bytes;


    logger->logInfo("Created base potentials.");

    return buffer;
}
*/

void CrowdCalculator::setOuterLoopCount(int outerLoopCount)
{
    potentialCalculator->setOuterLoopCount(outerLoopCount);
}


void CrowdCalculator::setCostWeightPathLength(float pathLength)
{
    costCalculator->setCostWeightPathLength(pathLength);
}


void CrowdCalculator::setCostWeightTime(float time)
{
    costCalculator->setCostWeightTime(time);
}


void CrowdCalculator::setCostWeightDiscomfort(float discomfort)
{
    costCalculator->setCostWeightDiscomfort(discomfort);
}

void CrowdCalculator::setMinimumDensity(float density)
{
    speedCalculator->setMinimumDensity(density);
}


void CrowdCalculator::setMaximumDensity(float density)
{
    speedCalculator->setMaximumDensity(density);
}


void CrowdCalculator::setMaximumSpeed(float speed)
{
    speedCalculator->setMaximumSpeed(speed);
}


float CrowdCalculator::getMinimumDensity()
{
    return speedCalculator->getMinimumDensity();
}


float CrowdCalculator::getMaximumDensity()
{
    return speedCalculator->getMaximumDensity();
}


void CrowdCalculator::setInnerLoopCount(uint count)
{
    potentialCalculator->setInnerLoopCount(static_cast<cl_uint> (count));
}


void CrowdCalculator::setIsBreakingAfterOuterStep(bool isBreakingAfterOuterStep)
{
    this->isBreakingAfterOuterStep = isBreakingAfterOuterStep;

    potentialCalculator->setIsBreakingAfterOuterStep(isBreakingAfterOuterStep);
}

/*
std::vector<Agent>* CrowdCalculator::getResolvedAgents()
{
    agentMover->getAgents(resolvedAgents);

    return &resolvedAgents;
}
*/

size_t CrowdCalculator::getBufferSideLength()
{
    return bufferSideLength;
}


size_t CrowdCalculator::getWorkGroupSideLength()
{
    return workGroupSideLength;
}


const BufferTexture* CrowdCalculator::getPositions() const
{
    return agentMover->getPositions();
}


const BufferTexture* CrowdCalculator::getDirections() const
{
    return agentMover->getDirections();
}


const BufferTexture* CrowdCalculator::getIds() const
{
    return agentMover->getIds();
}


const BufferTexture* CrowdCalculator::getRadii() const
{
    return agentMover->getRadii();
}


float CrowdCalculator::getMaximumSpeed() const
{
    return speedCalculator->getMaximumSpeed();
}


void CrowdCalculator::rewind()
{
    agentMover->setAgents(originalAgents);
    agentMover->setAgentCounts(originalAgentCounts);
}


Vector4 CrowdCalculator::getDensityDiscomfortVelocity(cl_uint positionX, cl_uint positionY)
{
    return splatterer->getDensityDiscomfortVelocity(positionX, positionY);
}


Vector4 CrowdCalculator::getSpeed(cl_uint positionX, cl_uint positionY)
{
    return speedCalculator->getSpeed(positionX, positionY);
}


Vector4 CrowdCalculator::getCost(cl_uint positionX, cl_uint positionY)
{
    return costCalculator->getCost(positionX, positionY);
}


Vector4 CrowdCalculator::getPotential(cl_uint positionX, cl_uint positionY)
{
    return potentialCalculator->getPotential(positionX, positionY);
}


void CrowdCalculator::getGradient(cl_uint positionX, cl_uint positionY, AgentGroupRenderState::State state, cl_float* gradientX, cl_float* gradientY)
{
    gradientCalculator->getGradient(positionX, positionY, state, gradientX, gradientY);
}


const BufferTexture* CrowdCalculator::getDiscomforts() const
{
    return discomforts;
}


const BufferTexture* CrowdCalculator::getCosts() const
{
    return costCalculator->getCosts();
}


const BufferTexture* CrowdCalculator::getSpeeds() const
{
    return speedCalculator->getSpeeds();
}


const Texture2D* CrowdCalculator::getDensitiesDiscomfortsVelocities() const
{
    return splatterer->getDensitiesDiscomfortsVelocities();
}


const BufferTexture* CrowdCalculator::getAverageVelocities() const
{
    return splatterer->getAverageVelocities();
}


const BufferTexture* CrowdCalculator::getPotentials() const
{
    return potentialCalculator->getPotentials();
}


const Texture2D* CrowdCalculator::getGradients01() const
{
    return gradientCalculator->getGradients01();
}


const Texture2D* CrowdCalculator::getGradients23() const
{
    return gradientCalculator->getGradients23();
}


const Texture2D* CrowdCalculator::getSplatAreas() const
{
    return splatterer->getSplatAreas();
}


const BufferTexture* CrowdCalculator::getWorkGroups() const
{
    return workGroupsCalculator->getWorkGroups();
}


const BufferTexture* CrowdCalculator::getWorkItems() const
{
    return workItemsCalculator->getWorkItems();
}


const BufferTexture* CrowdCalculator::getGroupStates(int index) const
{
    return potentialCalculator->getGroupStates(index);
}


GLint CrowdCalculator::getGroupStatesReadIndex() const
{
    return potentialCalculator->getGroupStatesReadIndex();
}


void CrowdCalculator::setUpdateState(UpdateState::State state)
{
    potentialCalculator->setUpdateState(state);
}


void CrowdCalculator::setExitMode(cl_int exitMode)
{
    this->exitMode = exitMode;
}


QString CrowdCalculator::getTotalBufferSizeMessage(int* const sum)
{
    QString message;
    int size;

#define PROCESS_CALCULATOR(CALCULATOR, NAME) \
{ \
    size = CALCULATOR->getTotalBufferSize(); \
    *sum += size; \
    message += String::formatMemoryString(NAME, size) + "\n"; \
}

    PROCESS_CALCULATOR(splatterer, "Splatterer ");
    PROCESS_CALCULATOR(costCalculator, "Cost Calculator ");
    PROCESS_CALCULATOR(speedCalculator, "Speed Calculator ");
    PROCESS_CALCULATOR(potentialCalculator, "Potential Calculator ");
    PROCESS_CALCULATOR(gradientCalculator, "Gradient Calculator ");
    PROCESS_CALCULATOR(agentMover, "Agent Mover ");
    PROCESS_CALCULATOR(collisionResolver, "Collision Resolver ");
    PROCESS_CALCULATOR(workGroupsCalculator, "Work Groups Calculator ");
    PROCESS_CALCULATOR(workItemsCalculator, "Work Items Calculator ");

    size = totalBufferSize;
    *sum += size;
    message += String::formatMemoryString("Crowd Calculator ", size) + "\n";

    return message;
}


void CrowdCalculator::setDiscomfortBrushRadius(float radius) const
{
    splatterer->setDiscomfortBrushRadius(radius);
}


void CrowdCalculator::setDiscomfortBrushIntensity(float intensity) const
{
    splatterer->setDiscomfortBrushIntensity(intensity);
}


void CrowdCalculator::setDiscomfortBrushPosition(float x, float y) const
{
    splatterer->setDiscomfortBrushPosition(x, y);
}


const std::vector<cl_uint> CrowdCalculator::getAgentCounts() const
{
    return agentMover->getAgentCounts();
}


void CrowdCalculator::checkEntryArea(Vector4i entry) const
{
    if (!checkArea(entry))
    {
        throw Exception("Invalid entry area defined!");
    }
}


bool CrowdCalculator::checkArea(Vector4i area) const
{
    return (area.x <= area.z) && (area.y <= area.w);
}
