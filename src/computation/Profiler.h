#ifndef PROFILER_H_
#define PROFILER_H_

#include <CL/cl.h>

#include <QString>
#include <vector>

#include "ProfilingElement.h"


/**
 * This asynchronous profiling macro conditionally adds a profiling event for each invocation.
 * Timing is done on the server side. The results can be queried later in the application.
 *
 * Use "&event" as event to pass to the command.
 *
 * Uses a clFinish on either side of the command to prevent batching of commands (e.g.
 * AMD's implementation combines multiple commands into batches and reports similar start
 * and end times for them (see AMD OpenCL Programming Guide 4.3.1)).
 */


#define CL_PROFILE(PROFILE_ELEMENT_ID, IS_ADDING_PROFILING_EVENT, QUEUE, COMMAND) \
{ \
    if ((IS_ADDING_PROFILING_EVENT)) \
    { \
        cl_event event; \
        clFinish(QUEUE); \
    \
        COMMAND; \
        clFinish(QUEUE); \
    \
        profiler->getElement(PROFILE_ELEMENT_ID).addEvent(event); \
    } \
    else \
    { \
        cl_event event; \
    \
        COMMAND; \
    } \
}

/**
 * This pair of profiling macros directly compute the execution time in the client
 * and stores it in the executionTime variable.
 * NOTE: It does a clFinish!
 */


#define CL_PROFILE_START(PROFILE_ELEMENT_ID) \
clFinish(queue); \
cl_uint PROFILE_ELEMENT_ID##Time = TimeHelper::getTime();


#define CL_PROFILE_END(PROFILE_ELEMENT_ID) \
clFinish(queue); \
PROFILE_ELEMENT_ID##Time = TimeHelper::getTime() - PROFILE_ELEMENT_ID##Time; \
getProfilingElement(PROFILE_ELEMENT_ID).executionTime += PROFILE_ELEMENT_ID##Time;


#define CL_PROFILE_CLIENT(CONDITION, CLIENT_PROFILER, TIME, QUEUE, COMMAND) \
{ \
    if (CONDITION) \
    { \
        clFinish(QUEUE); \
        CLIENT_PROFILER->start(&(CLIENT_PROFILER->TIME)); \
        COMMAND; \
        clFinish(QUEUE); \
        CLIENT_PROFILER->stop(&(CLIENT_PROFILER->TIME)); \
    } \
    else \
    { \
        COMMAND; \
    } \
}


#define GL_PROFILE_CLIENT(CONDITION, CLIENT_PROFILER, TIME, COMMAND) \
{ \
    if (CONDITION) \
    { \
        glFinish(); \
        CLIENT_PROFILER->start(&(CLIENT_PROFILER->TIME)); \
        COMMAND; \
        glFinish(); \
        CLIENT_PROFILER->stop(&(CLIENT_PROFILER->TIME)); \
    } \
    else \
    { \
        COMMAND; \
    } \
}


class Profiler
{
public:
                        Profiler();
	virtual             ~Profiler();

	/**
	 * If sum pointers are not NULL times are added to sums.
	 */

	QString             computeElementsString(cl_ulong* launchTimeSum, cl_ulong* executionTimeSum);

	/**
	 * Clears the list of events and sets the times to zero in the elements.
	 */

	void                resetElements();

	size_t              registerElement(QString name);
	void                deregisterElement(QString name);

	ProfilingElement&   getElement(size_t id);

private:

	std::vector<ProfilingElement>   elements;
};

#endif /* PROFILER_H_ */
