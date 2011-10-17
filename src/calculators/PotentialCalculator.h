#ifndef POTENTIALCALCULATOR_H_
#define POTENTIALCALCULATOR_H_

#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../graphics/BufferTexture.h"
#include "../graphics/TextureBufferTripple.h"

#include "../computation/Program.h"
#include "SharedBufferCalculator.h"

#include "../Logger.h"
#include "../Vector4.h"


#include "../States.h"

/**
 * Contains base potential in sharedTextureBuffer[1].
 * Computes current potential on sharedTextureBuffer[0].
 */

class PotentialCalculator : public SharedBufferCalculator
{
public:

    static const QString       PROFILING_ELEMENT_NAME;

    static const Vector4i      SMALL_UPDATE_VECTOR4I;
    static const Vector4i      CONVERGED_VECTOR4I;

    static const cl_int        UPDATE_METHOD_UPDATE_ALL;
    static const cl_int        UPDATE_METHOD_UPDATE_SELECTIVELY;

    static const int           INNER_LOOP_UNROLL_FACTOR    = 2;

                PotentialCalculator(const Logger*       logger,
                                    Profiler*           profiler,
                                    const Context*      context,
                                    size_t              threadCount,
                                    size_t              workGroupSize,
                                    cl_uint             bufferSideLength,
                                    GLsizeiptr          bufferByteSize,
                                    cl_mem              basePotential,
                                    cl_uint             workGroupSideLength);
    virtual     ~PotentialCalculator();


                /**
                 * Returns true if the computed result is a converged result.
                 * When not stepping always the converged result is computed, if stepping
                 * a intermediate result is possible.
                 */

    bool        compute(bool isProfiling, cl_mem sharedTextureBufferCost);


    void        setOuterLoopCount(int outerLoopCount);
    size_t      getOuterLoopCount();

    void        setIsBreakingAfterOuterStep(bool isBreaking);

    void        setInnerLoopCount(cl_uint count);

    Vector4     getPotential(cl_uint positionX, cl_uint positionY);

    cl_mem      getPotentialsShared();

    const BufferTexture*    getPotentials() const;

    const BufferTexture*    getGroupStates(int index) const;

    int         getGroupStatesReadIndex() const;


    void        setUpdateState(UpdateState::State state);


private:

    cl_kernel           kernelInit;
    cl_kernel           kernelSolveLarge;

    TextureBufferTripple*               baseGroupStates;
    std::vector<TextureBufferTripple*>  groupStates;

    cl_mem              nullBuffer;

    int                 groupStatesReadIndex;
    int                 groupStatesWriteIndex;

    size_t              outerLoopCount;

    bool                wasConverged;
    size_t              iCurrent;
    bool                isBreakingAfterOuterStep;

    bool                isOnlyInitializingFirst;
    bool                isFirstStep;

    size_t              kernelSolveLargeProfilingId;

    cl_uint             innerLoopCount;

    cl_uint             workGroupSideLength;

    UpdateState::State  updateState;

    cl_mem              basePotential;
};

#endif /* POTENTIALCALCULATOR_H_ */
