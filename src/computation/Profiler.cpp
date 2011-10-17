#include "Profiler.h"

#include "../String.h"


Profiler::Profiler()
{
}


Profiler::~Profiler()
{
}


QString Profiler::computeElementsString(cl_ulong* launchTimeSum, cl_ulong* executionTimeSum)
{
    std::vector<ProfilingElement>::iterator iter;

    QString s = "";

    for (iter = elements.begin(); iter != elements.end(); ++iter)
    {
        ProfilingElement& element = *iter;

        element.evaluateEvents();

        cl_ulong launchTime = element.startAverage - element.queuedAverage;

        if (launchTimeSum != NULL)
        {
            *launchTimeSum += launchTime;
        }

        cl_ulong executionTime = element.endAverage - element.startAverage;

        if (executionTimeSum != NULL)
        {
            *executionTimeSum += executionTime;
        }

        if (iter != elements.begin())
        {
            s += "\n";
        }

//        s += String::formatProfilingString(e);
        s += String::formatProfilingString(element.name, launchTime, executionTime);
//        s += StringHelper::formatProfilingString(e.name, 0, e.executionTime);
    }

    return s;
}


void Profiler::resetElements()
{
    std::vector<ProfilingElement>::iterator iter;


    for (iter = elements.begin(); iter != elements.end(); ++iter)
    {
        iter->reset();
    }
}


size_t Profiler::registerElement(QString name)
{
    ProfilingElement element;

    element.name = name;
    element.reset();

    elements.push_back(element);

    return elements.size() - 1;
}


void Profiler::deregisterElement(QString name)
{
    std::vector<ProfilingElement>::iterator iterator;

    for (iterator = elements.begin(); iterator != elements.end(); ++iterator)
    {
        if ((*iterator).name == name)
        {
            elements.erase(iterator);
            break;
        }
    }
}


ProfilingElement& Profiler::getElement(size_t id)
{
    return elements.at(id);
}
