#ifndef AGENT_H_
#define AGENT_H_

#include <CL/cl.h>


struct Agent
{
    cl_float2   position;
    cl_float2   direction;

    cl_float    speed;
    cl_float    maximumSpeed;

    cl_float    radius;
    cl_uint     id;             // group and type

    cl_float    turnRate;
};


#endif /* AGENT_H_ */
