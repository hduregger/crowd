#ifndef GRADIENTCALCULATOR_H_
#define GRADIENTCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/Texture2D.h"
#include "../graphics/Texture2DPair.h"

#include "../computation/Program.h"

#include "SharedBufferCalculator.h"

#include "../States.h"


class GradientCalculator : public SharedBufferCalculator
{
public:

    static const QString PROFILING_ELEMENT_NAME;

                        GradientCalculator( const Logger*       logger,
                                            Profiler*           profiler,
                                            const Context*      context,
                                            size_t              threadCount,
                                            size_t              workGroupSize,
                                            cl_uint             bufferSideLength,
                                            GLsizeiptr          bufferByteSize);
    virtual             ~GradientCalculator();

    void                compute(bool isProfiling, cl_mem sharedPotentialBuffer);

    void                getGradient(cl_uint positionX, cl_uint positionY, AgentGroupRenderState::State state, cl_float* gradientX, cl_float* gradientY);

    cl_mem              getGradients01Shared();
    cl_mem              getGradients23Shared();

    const Texture2D*    getGradients01() const;
    const Texture2D*    getGradients23() const;

private:

    cl_kernel           kernelGradient;
    size_t              kernelGradientProfilingId;

    Texture2DPair*      image01;
    Texture2DPair*      image23;
};

#endif /* GRADIENTCALCULATOR_H_ */
