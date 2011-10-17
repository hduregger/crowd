#ifndef AVERAGEVELOCITYCALCULATOR_H_
#define AVERAGEVELOCITYCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"


class AverageVelocityCalculator : public SharedBufferCalculator
{
public:

    static const QString PROFILING_ELEMENT_NAME;

                    AverageVelocityCalculator(  const Logger*       logger,
                                                Profiler*           profiler,
                                                const Context*      context,
                                                size_t              threadCount,
                                                size_t              workGroupSize,
                                                cl_uint             bufferSideLength,
                                                GLsizeiptr          bufferByteSize);
    virtual         ~AverageVelocityCalculator();

    void            compute(bool isProfiling, cl_mem densityDiscomfortVelocity);

private:

    cl_kernel       kernelAverageVelocity;
    size_t          kernelAverageVelocityProfilingId;
};

#endif /* AVERAGEVELOCITYCALCULATOR_H_ */
