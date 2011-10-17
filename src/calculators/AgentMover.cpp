#include "AgentMover.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"
#include "../SystemTime.h"

#include <CL/cl_gl.h>

#include "../Agent.h"

const QString AgentMover::PROFILING_ELEMENT_NAME = "  Move";

const cl_int  AgentMover::EXIT_MODE_PARK         = 0;
const cl_int  AgentMover::EXIT_MODE_CHANGE_GROUP = 1;
const cl_int  AgentMover::EXIT_MODE_RESPAWN      = 2;


AgentMover::AgentMover( const Context*      context,
                        Profiler*           profiler,
                        size_t              workGroupSize,
                        cl_uint             bufferSideLength,
                        size_t              count,
                        cl_uint             areaSideLength,
                        Vector4i            agentEntry0,
                        Vector4i            agentEntry1,
                        Vector4i            agentEntry2,
                        Vector4i            agentEntry3,
                        std::vector<cl_uint>& agentCountsVector)
:   program(NULL),
    context(context),
    kernelAgentMovement(NULL),
    workGroupSize(workGroupSize),
    bufferSideLength(bufferSideLength),
    agentEntries(NULL),
    agentCounts(NULL),
    count(count),
    positions(NULL),
    directions(NULL),
    speeds(NULL),
    maximumSpeeds(NULL),
    ids(NULL),
    radii(NULL),
    turnRates(NULL),
    totalBufferSize(0),
    profiler(profiler)
{
    // Create program

    program = new Program("src/kernels/move.cl", context, "");


    // Create kernels

    cl_int status;

    kernelAgentMovement = clCreateKernel(program->getProgram(), "move", &status);
    CL_ERROR(status);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelAgentMovement,  0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 12, sizeof(cl_float), &areaSideLength ) );


    // Write entry positions into buffer

    std::vector<cl_int> data(16);

    data[ 0] = agentEntry0.x;
    data[ 1] = agentEntry0.y;
    data[ 2] = agentEntry0.z;
    data[ 3] = agentEntry0.w;

    data[ 4] = agentEntry1.x;
    data[ 5] = agentEntry1.y;
    data[ 6] = agentEntry1.z;
    data[ 7] = agentEntry1.w;

    data[ 8] = agentEntry2.x;
    data[ 9] = agentEntry2.y;
    data[10] = agentEntry2.z;
    data[11] = agentEntry2.w;

    data[12] = agentEntry3.x;
    data[13] = agentEntry3.y;
    data[14] = agentEntry3.z;
    data[15] = agentEntry3.w;

    agentEntries = clCreateBuffer(context->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_int) * 16, &data[0], &status);

    agentCounts  = clCreateBuffer(context->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * 8, &agentCountsVector[0], &status);

    CL_ERROR(status);
    totalBufferSize += sizeof(cl_int) * 16;

    // Create agent property buffers

    positions       = new TextureBufferTripple(sizeof(cl_float2) * count, NULL, GL_DYNAMIC_COPY, GL_RG32F, CL_MEM_READ_WRITE, context);
    directions      = new TextureBufferTripple(sizeof(cl_float2) * count, NULL, GL_DYNAMIC_COPY, GL_RG32F, CL_MEM_READ_WRITE, context);
    speeds          = new TextureBufferTripple(sizeof(cl_float)  * count, NULL, GL_DYNAMIC_COPY, GL_R32F,  CL_MEM_READ_WRITE, context);
    maximumSpeeds   = new TextureBufferTripple(sizeof(cl_float)  * count, NULL, GL_DYNAMIC_COPY, GL_R32F,  CL_MEM_READ_WRITE, context);
    ids             = new TextureBufferTripple(sizeof(cl_uint)   * count, NULL, GL_DYNAMIC_COPY, GL_R32UI, CL_MEM_READ_WRITE, context);
    radii           = new TextureBufferTripple(sizeof(cl_float)  * count, NULL, GL_DYNAMIC_COPY, GL_R32F,  CL_MEM_READ_WRITE, context);
    turnRates       = new TextureBufferTripple(sizeof(cl_float)  * count, NULL, GL_DYNAMIC_COPY, GL_R32F,  CL_MEM_READ_WRITE, context);

    totalBufferSize += sizeof(cl_float2) * count;
    totalBufferSize += sizeof(cl_float2) * count;
    totalBufferSize += sizeof(cl_float)  * count;
    totalBufferSize += sizeof(cl_float)  * count;
    totalBufferSize += sizeof(cl_uint)   * count;
    totalBufferSize += sizeof(cl_float)  * count;
    totalBufferSize += sizeof(cl_float)  * count;


    kernelMoveProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);
}


AgentMover::~AgentMover()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);

    delete program;

    clReleaseMemObject(agentEntries);
    clReleaseMemObject(agentCounts);

    clReleaseKernel(kernelAgentMovement);

    delete positions;
    delete directions;
    delete speeds;
    delete maximumSpeeds;
    delete ids;
    delete radii;
    delete turnRates;
}


const BufferTexture* AgentMover::getPositions() const
{
    return positions->getBufferTexture();
}


const BufferTexture* AgentMover::getDirections() const
{
    return directions->getBufferTexture();
}


const BufferTexture* AgentMover::getSpeeds() const
{
    return speeds->getBufferTexture();
}


const BufferTexture* AgentMover::getIds() const
{
    return ids->getBufferTexture();
}


const BufferTexture* AgentMover::getRadii() const
{
    return radii->getBufferTexture();
}


size_t AgentMover::getCount()
{
    return count;
}


cl_mem AgentMover::getPositionsShared()
{
    return positions->getBufferShared();
}


cl_mem AgentMover::getRadiiShared()
{
    return radii->getBufferShared();
}


cl_mem AgentMover::getIdsShared()
{
    return ids->getBufferShared();
}


void AgentMover::compute(bool     isProfiling,
                         cl_mem   sharedGradientImage01,
                         cl_mem   sharedGradientImage23,
                         cl_mem   speedField,
                         cl_float deltaTime,
                         cl_int   exitMode,
                         cl_mem   potentials)
{
    //
    // Compute new positions and write out sort keys
    //

    cl_mem positionsBuffer      = positions->getBufferShared();
    cl_mem directionsBuffer     = directions->getBufferShared();
    cl_mem speedsBuffer         = speeds->getBufferShared();
    cl_mem maximumSpeedsBuffer  = maximumSpeeds->getBufferShared();
    cl_mem idsBuffer            = ids->getBufferShared();
    cl_mem radiiBuffer          = radii->getBufferShared();
    cl_mem turnRatesBuffer      = turnRates->getBufferShared();

    cl_command_queue queue = context->queue;

    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &positionsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &directionsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &speedsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &maximumSpeedsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &idsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &radiiBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &turnRatesBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedGradientImage01, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedGradientImage23, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &speedField, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &potentials, 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(kernelAgentMovement,  1, sizeof(cl_mem),   &sharedGradientImage01 ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  2, sizeof(cl_mem),   &sharedGradientImage23 ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  3, sizeof(cl_mem),   &positionsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  4, sizeof(cl_mem),   &directionsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  5, sizeof(cl_mem),   &speedsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  6, sizeof(cl_mem),   &maximumSpeedsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  7, sizeof(cl_mem),   &idsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  8, sizeof(cl_mem),   &radiiBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement,  9, sizeof(cl_mem),   &turnRatesBuffer ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 10, sizeof(cl_mem),   &speedField ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 11, sizeof(cl_float), &deltaTime ) );

    CL_ERROR( clSetKernelArg(kernelAgentMovement, 13, sizeof(cl_mem),   &potentials ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 14, sizeof(cl_mem),   &agentEntries ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 15, sizeof(cl_int),   &exitMode ) );
    CL_ERROR( clSetKernelArg(kernelAgentMovement, 16, sizeof(cl_mem),   &agentCounts ) );

    if (count >= workGroupSize)
    {
        CL_PROFILE(kernelMoveProfilingId, isProfiling, queue,
                CL_ERROR( clEnqueueNDRangeKernel(queue, kernelAgentMovement, 1, NULL, &count, &workGroupSize, 0, NULL, &event) )
        );
    }
    else
    {
        CL_PROFILE(kernelMoveProfilingId, isProfiling, queue,
                CL_ERROR( clEnqueueNDRangeKernel(queue, kernelAgentMovement, 1, NULL, &count, &count, 0, NULL, &event) )
        );
    }

    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &potentials, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &speedField, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedGradientImage01, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedGradientImage23, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &turnRatesBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &radiiBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &idsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &maximumSpeedsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &speedsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &directionsBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &positionsBuffer, 0, NULL, NULL) );
}


void AgentMover::setAgents(const std::vector<Agent>& agentsVector)
{
    if (agentsVector.size() != count)
    {
        throw Exception("AgentMover::setAgents: number of agents does not match previously set count");
    }

    // Accessing shared buffer through OpenGL or else content would go random when acquiring the buffer with OpenCL lateron.

    BuffersMapping mapping = mapBuffers(GL_WRITE_ONLY);

    std::vector<Agent>::const_iterator iter;

    size_t i = 0;

    for (iter = agentsVector.begin(); iter != agentsVector.end(); ++iter)
    {
        mapping.positions[i]      = (*iter).position;
        mapping.directions[i]     = (*iter).direction;
        mapping.speeds[i]         = (*iter).speed;
        mapping.maximumSpeeds[i]  = (*iter).maximumSpeed;
        mapping.radii[i]          = (*iter).radius;
        mapping.ids[i]            = (*iter).id;
        mapping.turnRates[i]      = (*iter).turnRate;

        i++;
    }

    unmapBuffers();
}


void AgentMover::getAgents(std::vector<Agent>& agentsVector) const
{
    // Accessing shared buffer through OpenGL or else content would go random when acquiring the buffer with OpenCL lateron.

    BuffersMapping mapping = mapBuffers(GL_READ_ONLY);

    std::vector<Agent>::iterator iter;

    size_t i = 0;

    for (iter = agentsVector.begin(); iter != agentsVector.end(); ++iter)
    {
        (*iter).position        = mapping.positions[i];
        (*iter).direction       = mapping.directions[i];
        (*iter).speed           = mapping.speeds[i];
        (*iter).maximumSpeed    = mapping.maximumSpeeds[i];
        (*iter).radius          = mapping.radii[i];
        (*iter).id              = mapping.ids[i];
        (*iter).turnRate        = mapping.turnRates[i];

        i++;
    }

    unmapBuffers();
}


AgentMover::BuffersMapping AgentMover::mapBuffers(GLenum access) const
{
    BuffersMapping mapping;

    glBindBuffer(GL_TEXTURE_BUFFER, positions->getBuffer());
    GL_ERROR;
    mapping.positions       = (cl_float2*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, directions->getBuffer());
    GL_ERROR;
    mapping.directions      = (cl_float2*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, speeds->getBuffer());
    GL_ERROR;
    mapping.speeds          = (cl_float*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, maximumSpeeds->getBuffer());
    GL_ERROR;
    mapping.maximumSpeeds   = (cl_float*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, ids->getBuffer());
    GL_ERROR;
    mapping.ids             = (cl_uint*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, radii->getBuffer());
    GL_ERROR;
    mapping.radii           = (cl_float*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, turnRates->getBuffer());
    GL_ERROR;
    mapping.turnRates       = (cl_float*) glMapBuffer(GL_TEXTURE_BUFFER, access);
    GL_ERROR;

    return mapping;
}


void AgentMover::unmapBuffers() const
{
    glBindBuffer(GL_TEXTURE_BUFFER, positions->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, directions->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, speeds->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, maximumSpeeds->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, ids->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, radii->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, turnRates->getBuffer());
    GL_ERROR;
    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, 0);
    GL_ERROR;
}


int AgentMover::getTotalBufferSize()
{
    return totalBufferSize;
}

const std::vector<cl_uint> AgentMover::getAgentCounts() const
{
    cl_int status;

    cl_uint* buffer = static_cast<cl_uint*> ( clEnqueueMapBuffer(context->queue,
                                                                 agentCounts,
                                                                 CL_TRUE,
                                                                 CL_MAP_READ,
                                                                 0,
                                                                 sizeof(cl_uint) * 8,
                                                                 0,
                                                                 NULL,
                                                                 NULL,
                                                                 &status) );
    CL_ERROR(status);

    std::vector<cl_uint> agentCountsVector(8);

    cl_uint i = 0;

    std::vector<cl_uint>::iterator iterator;

    for (iterator = agentCountsVector.begin(); iterator != agentCountsVector.end(); ++iterator)
    {
        *iterator = buffer[i];

        i++;
    }

    clEnqueueUnmapMemObject(context->queue, agentCounts, buffer, 0, NULL, NULL);

    return agentCountsVector;
}


void AgentMover::setAgentCounts(const std::vector<cl_uint>& agentCountsVector)
{
    cl_int status;

    cl_uint* buffer = static_cast<cl_uint*> ( clEnqueueMapBuffer(context->queue,
                                                                 agentCounts,
                                                                 CL_TRUE,
                                                                 CL_MAP_WRITE,
                                                                 0,
                                                                 sizeof(cl_uint) * 8,
                                                                 0,
                                                                 NULL,
                                                                 NULL,
                                                                 &status) );
    CL_ERROR(status);

    cl_uint i = 0;

    std::vector<cl_uint>::const_iterator iterator;

    for (iterator = agentCountsVector.begin(); iterator != agentCountsVector.end(); ++iterator)
    {
        buffer[i] = *iterator;

        i++;
    }

    clEnqueueUnmapMemObject(context->queue, agentCounts, buffer, 0, NULL, NULL);
}


/*
void AgentMover::logAgentsData(Logger* logger)
{
    std::vector<Vector4> agents(count);

    getAgents(agents);

    std::vector<Vector4>::const_iterator iter;

    QString s;

    int i = 0;

    for (iter = agents.begin(); iter != agents.end(); ++iter)
    {
        if (i > 5)
        {
            s += "...";

            break;
        }

        s += (*iter).toString() + " ";

        i++;
    }

    logger->logInfo(s);
}
*/
