#ifndef WORKGROUPCALCULATOR_H_
#define WORKGROUPCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"


class WorkGroupCalculator : public SharedBufferCalculator
{
public:
                WorkGroupCalculator(const Logger*   logger,
                                    Profiler*       profiler,
                                    const Context*  context,
                                    size_t          threadCount,
                                    size_t          workGroupSize,
                                    cl_uint         bufferSideLength,
                                    GLsizeiptr      bufferByteSize,
                                    cl_uint         workGroupSideLength);
    virtual     ~WorkGroupCalculator();

    void        compute();

    const BufferTexture*    getWorkGroups() const;

private:

    cl_kernel           kernelWorkGroups;
};

#endif /* WORKGROUPCALCULATOR_H_ */
