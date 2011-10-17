#ifndef AGENTMOVER_H_
#define AGENTMOVER_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../computation/Program.h"
#include "../computation/Context.h"
#include "../computation/Profiler.h"
#include "../Vector4.h"
#include "../Logger.h"
#include "../graphics/BufferTexture.h"
#include "../graphics/TextureBufferTripple.h"

#include <vector>

#include "../Agent.h"


class AgentMover
{
public:

    static const QString    PROFILING_ELEMENT_NAME;

    static const cl_int     EXIT_MODE_PARK;
    static const cl_int     EXIT_MODE_CHANGE_GROUP;
    static const cl_int     EXIT_MODE_RESPAWN;

                            AgentMover( const Context*        context,
                                        Profiler*             profiler,
                                        size_t                workGroupSize,
                                        cl_uint               bufferSideLength,
                                        size_t                count,
                                        cl_uint               areaSideLength,
                                        Vector4i              agentEntry0,
                                        Vector4i              agentEntry1,
                                        Vector4i              agentEntry2,
                                        Vector4i              agentEntry3,
                                        std::vector<cl_uint>& agentCountsVector);
    virtual                 ~AgentMover();

    void                    compute(bool     isProfiling,
                                    cl_mem   sharedGradientImage01,
                                    cl_mem   sharedGradientImage23,
                                    cl_mem   speedField,
                                    cl_float deltaTime,
                                    cl_int   exitMode,
                                    cl_mem   potentials);

    const BufferTexture*    getPositions() const;
    const BufferTexture*    getDirections() const;
    const BufferTexture*    getSpeeds() const;
    const BufferTexture*    getIds() const;
    const BufferTexture*    getRadii() const;

    void                    setAgents(const std::vector<Agent>& agentsVector);
    void                    getAgents(std::vector<Agent>& agentsVector) const;

//    void                    logAgentsData(Logger* logger);

    size_t                  getCount();

    cl_mem                  getPositionsShared();
    cl_mem                  getRadiiShared();
    cl_mem                  getIdsShared();

    int                     getTotalBufferSize();

    const std::vector<cl_uint> getAgentCounts() const;
    void                       setAgentCounts(const std::vector<cl_uint>& agentCountsVector);

private:

    Program*                program;
    const Context*          context;
    cl_kernel               kernelAgentMovement;

    size_t                  workGroupSize;
    cl_uint                 bufferSideLength;

    cl_mem                  agentEntries;
    cl_mem                  agentCounts;

    size_t                  count;

    TextureBufferTripple*   positions;
    TextureBufferTripple*   directions;
    TextureBufferTripple*   speeds;
    TextureBufferTripple*   maximumSpeeds;
    TextureBufferTripple*   ids;
    TextureBufferTripple*   radii;
    TextureBufferTripple*   turnRates;

    int                     totalBufferSize;

    Profiler*               profiler;
    size_t                  kernelMoveProfilingId;

    struct BuffersMapping
    {
        cl_float2*          positions;
        cl_float2*          directions;
        cl_float*           speeds;
        cl_float*           maximumSpeeds;
        cl_uint*            ids;
        cl_float*           radii;
        cl_float*           turnRates;
    };


    /**
     * Map all buffers.
     * access is e.g. GL_WRITE_ONLY.
     */

    BuffersMapping          mapBuffers(GLenum access) const;
    void                    unmapBuffers() const;
};

#endif /* AGENTMOVER_H_ */
