#include "ClientProfile.h"

#include "../String.h"
#include "../SystemTime.h"


ClientProfile::ClientProfile(cl_ulong stepLimit)
:   writeDiscomfortTime(0),
    splatTime(0),
    readSplatBuffersTime(0),
    computeAverageVelocityTime(0),
    computeSpeedTime(0),
    computeCostTime(0),
    computePotentialTime(0),
    computeGradientTime(0),
    resolveCollisionsTime(0),
    moveAgentsTime(0),
    renderTime(0),
    computationAndRenderTime(0),
    overheadTime(0),
    stepLimit(stepLimit),
    steps(0)
{
}


ClientProfile::~ClientProfile()
{
}


void ClientProfile::clear()
{
    writeDiscomfortTime         = 0;
    splatTime                   = 0;
    readSplatBuffersTime        = 0;
    computeAverageVelocityTime  = 0;
    computeSpeedTime            = 0;
    computeCostTime             = 0;
    computePotentialTime        = 0;
    computeGradientTime         = 0;
    resolveCollisionsTime       = 0;
    moveAgentsTime              = 0;
    renderTime                  = 0;
    computationAndRenderTime    = 0;
    overheadTime                = 0;
}


QString ClientProfile::getResults(bool isDetailedResult)
{
    QString profilingString;

    if (isDetailedResult)
    {
        profilingString += String::formatProfilingString("Write discomfort", 0, writeDiscomfortTime) + "\n";
        profilingString += String::formatProfilingString("Splat densities", 0, splatTime) + "\n";
        profilingString += String::formatProfilingString("Read splat buffer", 0, readSplatBuffersTime) + "\n";
        profilingString += String::formatProfilingString("Compute average velocity", 0, computeAverageVelocityTime) + "\n";
        profilingString += String::formatProfilingString("Compute speed", 0, computeSpeedTime) + "\n";
        profilingString += String::formatProfilingString("Compute cost", 0, computeCostTime) + "\n";
        profilingString += String::formatProfilingString("Compute potential", 0, computePotentialTime) + "\n";
        profilingString += String::formatProfilingString("Compute gradient", 0, computeGradientTime) + "\n";

        profilingString += "--------------------------------------------------\n";

        cl_ulong continuumSum =   writeDiscomfortTime
                                + splatTime
                                + readSplatBuffersTime
                                + computeAverageVelocityTime
                                + computeSpeedTime
                                + computeCostTime
                                + computePotentialTime
                                + computeGradientTime;

        profilingString += String::formatProfilingString("Continuum sum", 0, continuumSum ) + "\n";

        profilingString += String::formatProfilingString("Move agents", 0, moveAgentsTime) + "\n";
        profilingString += String::formatProfilingString("Resolve collisions", 0, resolveCollisionsTime) + "\n";

        profilingString += "--------------------------------------------------\n";
        profilingString += String::formatProfilingString("Computation sum", 0, continuumSum + resolveCollisionsTime + moveAgentsTime) + "\n";
    }

    profilingString += String::formatProfilingString("Render agents", 0, renderTime) + "\n";

    profilingString += "--------------------------------------------------\n";
    profilingString += String::formatProfilingString("Computation and render", 0, computationAndRenderTime) + "\n";
    profilingString += String::formatProfilingString("Overhead", 0, overheadTime) + "\n";
    profilingString += String::formatProfilingString("Total", 0, overheadTime + computationAndRenderTime);

    return profilingString;
}


void ClientProfile::start(cl_ulong* clientProfileTimeField)
{
    //
    // (t_end_0 - t_start_0) + (t_end_1 - t_start_1) + ... = -t_start_0 + t_end_0 - t_start_1 + t_end_1 - ...
    // NOTE: integer does underflow though when starting out as 0 which seems ok with C standard though.
    //

    *clientProfileTimeField -= SystemTime::getTime();
}


void ClientProfile::stop(cl_ulong* clientProfileTimeField)
{
    *clientProfileTimeField += SystemTime::getTime();
}


bool ClientProfile::step()
{
    steps++;

    if (steps >= stepLimit)
    {
        evaluate();

        steps = 0;

        return true;
    }

    return false;
}


void ClientProfile::evaluate()
{
    writeDiscomfortTime         /= stepLimit;
    splatTime                   /= stepLimit;
    readSplatBuffersTime        /= stepLimit;

    computeAverageVelocityTime  /= stepLimit;
    computeSpeedTime            /= stepLimit;
    computeCostTime             /= stepLimit;
    computePotentialTime        /= stepLimit;
    computeGradientTime         /= stepLimit;
    resolveCollisionsTime       /= stepLimit;
    moveAgentsTime              /= stepLimit;

    renderTime                  /= stepLimit;

    computationAndRenderTime    /= stepLimit;

    overheadTime                /= stepLimit;
}
