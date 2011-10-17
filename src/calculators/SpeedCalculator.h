#ifndef SPEEDCALCULATOR_H_
#define SPEEDCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../computation/Program.h"

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"

/**
 * The 4 components of each float4 are directional speed values.
 */

class SpeedCalculator : public SharedBufferCalculator
{
public:

    static const QString PROFILING_ELEMENT_NAME;

                            SpeedCalculator(    const Logger*       logger,
                                                Profiler*           profiler,
                                                const Context*      context,
                                                size_t              threadCount,
                                                size_t              workGroupSize,
                                                cl_uint             bufferSideLength,
                                                GLsizeiptr          bufferByteSize);
    virtual                 ~SpeedCalculator();

    void                    compute(bool isProfiling, cl_mem sharedDensityDiscomfortVelocity);

    void                    setMinimumDensity(float density);
    void                    setMaximumDensity(float density);

    float                   getMinimumDensity();
    float                   getMaximumDensity();

    void                    setMaximumSpeed(float speed);
    float                   getMaximumSpeed() const;

    Vector4                 getSpeed(cl_uint positionX, cl_uint positionY);

    cl_mem                  getSpeedsShared();

    const BufferTexture*    getSpeeds() const;

private:

    cl_kernel               speed;
    size_t                  speedProfilingId;

    float                   minimumDensity;
    float                   maximumDensity;
    float                   maximumSpeed;
};

#endif /* SPEEDCALCULATOR_H_ */
