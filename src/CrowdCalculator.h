#ifndef CROWDCALCULATOR_H_
#define CROWDCALCULATOR_H_

#include <QtGui>


#include "Logger.h"
#include "computation/ClientProfile.h"

#define GL3_PROTOTYPES 1
#include "graphics/gl3.h"

#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <GL/glx.h>

#include "calculators/Splatterer.h"
#include "calculators/WorkGroupCalculator.h"
#include "calculators/WorkItemCalculator.h"
#include "calculators/PotentialCalculator.h"
#include "calculators/GradientCalculator.h"
#include "calculators/AgentMover.h"
#include "calculators/SpeedCalculator.h"
#include "calculators/CostCalculator.h"
#include "calculators/AverageVelocityCalculator.h"
#include "calculators/CollisionResolver.h"

#include "graphics/BufferTexture.h"
#include "graphics/Texture2D.h"

#include "States.h"
#include "Settings.h"


class CrowdCalculator
{
public:

    static const float          DENSITY_THRESHOLD           = 0.5f;


                                CrowdCalculator(const Logger*   logger,
                                                Profiler*       profiler,
                                                Display*        displayX11,
                                                GLXContext      contextGLX,
                                                const Settings* settings);
    virtual                     ~CrowdCalculator();

    void                        setOuterLoopCount(int outerLoopCount);

    void                        setCostWeightPathLength(float pathLength);
    void                        setCostWeightTime(float time);
    void                        setCostWeightDiscomfort(float discomfort);

    void                        setMinimumDensity(float density);
    void                        setMaximumDensity(float density);

    void                        setMaximumSpeed(float speed);

    float                       getMinimumDensity();
    float                       getMaximumDensity();

    void                        setInnerLoopCount(uint count);

    void                        setIsBreakingAfterOuterStep(bool isBreakingAfterStep);

    void                        compute(ClientProfile* clientProfile, bool isProfiling, bool isResolvingCollisions, cl_float deltaTime);

    size_t                      getBufferSideLength();
    size_t                      getWorkGroupSideLength();

    float                       getMaximumSpeed() const;

    void                        rewind();

    Vector4                     getDensityDiscomfortVelocity(cl_uint positionX, cl_uint positionY);
    Vector4                     getSpeed(cl_uint positionX, cl_uint positionY);
    Vector4                     getCost(cl_uint positionX, cl_uint positionY);
    Vector4                     getPotential(cl_uint positionX, cl_uint positionY);
    void                        getGradient(cl_uint positionX,
                                            cl_uint positionY,
                                            AgentGroupRenderState::State state,
                                            cl_float* gradientX,
                                            cl_float* gradientY);

    const BufferTexture*        getPositions() const;
    const BufferTexture*        getDirections() const;
    const BufferTexture*        getIds() const;
    const BufferTexture*        getRadii() const;

    const BufferTexture*        getDiscomforts() const;
    const BufferTexture*        getCosts() const;
    const BufferTexture*        getSpeeds() const;
    const Texture2D*            getDensitiesDiscomfortsVelocities() const;
    const BufferTexture*        getAverageVelocities() const;
    const BufferTexture*        getPotentials() const;
    const Texture2D*            getGradients01() const;
    const Texture2D*            getGradients23() const;
    const Texture2D*            getSplatAreas() const;

    const BufferTexture*        getWorkGroups() const;
    const BufferTexture*        getWorkItems() const;

    const BufferTexture*        getGroupStates(int index) const;
    GLint                       getGroupStatesReadIndex() const;

    void                        setUpdateState(UpdateState::State state);

    void                        setExitMode(cl_int exitMode);

    QString                     getTotalBufferSizeMessage(int* const sum);

    void                        setDiscomfortBrushRadius(float radius) const;
    void                        setDiscomfortBrushIntensity(float intensity) const;
    void                        setDiscomfortBrushPosition(float x, float y) const;

    const std::vector<cl_uint>  getAgentCounts() const;

private:

    const Logger*               logger;

    Context*                    context;

    Splatterer*                 splatterer;


    WorkGroupCalculator*        workGroupsCalculator;
    WorkItemCalculator*         workItemsCalculator;

    PotentialCalculator*        potentialCalculator;
    GradientCalculator*         gradientCalculator;
    CostCalculator*             costCalculator;
    AverageVelocityCalculator*  averageVelocityCalculator;
    SpeedCalculator*            speedCalculator;

    CollisionResolver*          collisionResolver;
    AgentMover*                 agentMover;

    QString                     discomfortFile;
    QString                     exitFile;

    std::vector<Agent>          originalAgents;
    std::vector<cl_uint>        originalAgentCounts;

    Vector4i                    agentEntry0;
    Vector4i                    agentEntry1;
    Vector4i                    agentEntry2;
    Vector4i                    agentEntry3;

    GLuint                      textureBufferDiscomfort;
    BufferTexture*              discomforts;

    cl_mem                      basePotential;

    size_t                      bufferSideLength;
    size_t                      workGroupSideLength;


    size_t                      elements;
    size_t                      components;
    size_t                      bytes;


    size_t                      workGroupSize;

    uint                        agentCount;

    float                       maximumRadius;

    int                         totalBufferSize;

    bool                        isBreakingAfterOuterStep;
    bool                        isPotentialConverged;
    bool                        isFirstUpdate;

    bool                        isUsingGPU;

    cl_int                      exitMode;

    void                        initializeOpenCL(Display* displayX11, GLXContext contextGLX, bool isProfilingQueue);
    void                        initializeCalculators(Profiler* profiler, cl_float minimumRadius, cl_float maximumRadius, int agentSeed);
    std::vector<Agent>          initializeAgents(cl_float minimumRadius, cl_float maximumRadius, int agentSeed);

    /**
     * Returns the side length of a square image.
     * Throws expection if image is not square or length is not a power of two.
     */

    void                        loadDiscomfortImage(QString            filename,
                                                    GLuint*            textureBufferDiscomfort,
                                                    BufferTexture**    sharedTextureBufferDiscomfortTexture);

    cl_mem                      loadExitImage(QString filename);

//    cl_mem                      createExits(Vector4i exit0, Vector4i exit1, Vector4i exit2, Vector4i exit3);

    void                        checkEntryArea(Vector4i entry) const;

    /**
     * Returns false if the area is invalid.
     */

    bool                        checkArea(Vector4i area) const;
};

#endif /* CROWDCALCULATOR_H_ */
