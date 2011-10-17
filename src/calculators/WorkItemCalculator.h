#ifndef WORKITEMCALCULATOR_H_
#define WORKITEMCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"


class WorkItemCalculator : public SharedBufferCalculator
{
public:
                WorkItemCalculator( const Logger*   logger,
                                    Profiler*       profiler,
                                    const Context*  context,
                                    size_t          threadCount,
                                    size_t          workGroupSize,
                                    cl_uint         bufferSideLength,
                                    GLsizeiptr      bufferByteSize,
                                    cl_uint         workGroupSideLength);
    virtual     ~WorkItemCalculator();

    void        compute();

    const BufferTexture*    getWorkItems() const;


private:

    cl_kernel           kernelWorkItems;
};

#endif /* WORKITEMCALCULATOR_H_ */
