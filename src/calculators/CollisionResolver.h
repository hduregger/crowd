#ifndef COLLISIONRESOLVER_H_
#define COLLISIONRESOLVER_H_


#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../computation/Context.h"
#include "../computation/Profiler.h"
#include "../computation/Program.h"
#include "../Logger.h"


class CollisionResolver
{
public:

    static const uint       BUCKET_ENTRIES;
    static const QString    PROFILING_ELEMENT_NAME0;
    static const QString    PROFILING_ELEMENT_NAME1;

                            CollisionResolver(  const Context*      context,
                                                Profiler*           profiler,
                                                size_t              workGroupSize,
                                                size_t              count,
                                                cl_uint             bufferSideLength);
    virtual                 ~CollisionResolver();

    void                    compute(bool        isProfiling,
                                    cl_mem      positions,
                                    cl_mem      radii,
                                    cl_mem      ids,
                                    cl_float    maximumRadius,
                                    cl_mem      sharedPotentials);

    int                     getTotalBufferSize();

private:

    Program*                program;

    const Context*          context;

    cl_kernel               zeroAgentCounts;
    cl_kernel               sortAgentsIntoBuckets;
    cl_kernel               resolveCollisions;

    size_t                  threadCount;
    size_t                  workGroupSize;

    size_t                  count;

    cl_mem                  buckets;
    cl_mem                  agentCounts;

    cl_uint                 bufferSideLength;

    size_t                  bucketCount;

    int                     totalBufferSize;


    Profiler*               profiler;
    size_t                  kernelSortAgentsIntoBucketsProfilingId;
    size_t                  kernelResolveCollisionsProfilingId;
};

#endif /* COLLISIONRESOLVER_H_ */
