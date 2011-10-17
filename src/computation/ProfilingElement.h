#ifndef PROFILINGELEMENT_H_
#define PROFILINGELEMENT_H_

#include <CL/cl.h>

#include <QString>
#include <vector>


struct ProfilingElement
{
public:

    QString                 name;

    cl_ulong                queuedAverage;
    cl_ulong                startAverage;
    cl_ulong                endAverage;

    std::vector<cl_event>   events;

    /**
     * Sets times to zero and clears events.
     */

    void        reset();

    /**
     * Adds the event to the list.
     */

    void        addEvent(cl_event event);

    /**
     * Computes the times.
     */

    void        evaluateEvents();

    /**
     * Sets the times to zero.
     */

    void        zeroTimes();
};

#endif /* PROFILINGELEMENT_H_ */
