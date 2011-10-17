#ifndef CLIENTPROFILE_H_
#define CLIENTPROFILE_H_

#include <QString>

#include <CL/cl.h>


struct ClientProfile
{
public:

    cl_ulong    writeDiscomfortTime;
    cl_ulong    splatTime;
    cl_ulong    readSplatBuffersTime;

    cl_ulong    computeAverageVelocityTime;
    cl_ulong    computeSpeedTime;
    cl_ulong    computeCostTime;
    cl_ulong    computePotentialTime;
    cl_ulong    computeGradientTime;

    cl_ulong    resolveCollisionsTime;
    cl_ulong    moveAgentsTime;

    cl_ulong    renderTime;

    cl_ulong    computationAndRenderTime;

    cl_ulong    overheadTime;

                ClientProfile(cl_ulong stepLimit);
    virtual     ~ClientProfile();



    /**
     * Clears the times to zero.
     */

    void        clear();

    /**
     * Starts the timer.
     */

    void        start(cl_ulong* clientProfileTimeField);

    /**
     * Stops the timer.
     */

    void        stop(cl_ulong*  clientProfileTimeField);

    /**
     * Returns true if the step limit has been reached and the results can
     * be retrieved.
     */

    bool        step();

    /**
     * Returns the results.
     */

    QString     getResults(bool isDetailedResult);

private:

    cl_ulong    stepLimit;
    cl_ulong    steps;

    void        evaluate();

};

#endif /* CLIENTPROFILE_H_ */
