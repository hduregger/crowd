#ifndef COSTCALCULATOR_H_
#define COSTCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"


class CostCalculator : public SharedBufferCalculator
{
public:

    static const QString PROFILING_ELEMENT_NAME;

                    CostCalculator( const Logger*       logger,
                                    Profiler*           profiler,
                                    const Context*      context,
                                    size_t              threadCount,
                                    size_t              workGroupSize,
                                    cl_uint             bufferSideLength,
                                    GLsizeiptr          bufferByteSize);
    virtual          ~CostCalculator();

    void            compute(bool isProfiling, cl_mem sharedSpeed, cl_mem sharedDiscomfort);

    cl_mem          getCostsShared();

    const BufferTexture*  getCosts() const;

    Vector4         getCost(cl_uint positionX, cl_uint positionY);

    void            setCostWeightPathLength(float pathLength);
    void            setCostWeightTime(float time);
    void            setCostWeightDiscomfort(float discomfort);


private:

    cl_kernel       kernelCost;
    size_t          kernelCostProfilingId;

    float           costWeightPathLength;
    float           costWeightTime;
    float           costWeightDiscomfort;
};

#endif /* COSTCALCULATOR_H_ */
