#include "ProfilingElement.h"


void ProfilingElement::reset()
{
    zeroTimes();

    events.clear();
}


void ProfilingElement::addEvent(cl_event event)
{
    events.push_back(event);
}


void ProfilingElement::evaluateEvents()
{
    zeroTimes();

    //
    // Sum up time differences
    //

    std::vector<cl_event>::const_iterator iter;

    for (iter = events.begin(); iter != events.end(); ++iter)
    {
        cl_event event = (*iter);

        cl_ulong queued;
        cl_ulong start;
        cl_ulong end;

        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &queued, NULL);
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,  sizeof(cl_ulong), &start,  NULL);
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,    sizeof(cl_ulong), &end,    NULL);

        queuedAverage += queued;
        startAverage  += start;
        endAverage    += end;
    }

    //
    // Compute mean
    //

    cl_ulong eventCount = events.size();

    if (eventCount > 1)
    {
        queuedAverage   /= eventCount;
        startAverage    /= eventCount;
        endAverage      /= eventCount;
    }
}


void ProfilingElement::zeroTimes()
{
    queuedAverage = 0;
    startAverage  = 0;
    endAverage    = 0;
}
