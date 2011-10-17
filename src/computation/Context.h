#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <CL/cl.h>


struct Context
{
public:
                        Context(cl_context          context,
                                cl_device_id        device,
                                cl_command_queue    queue);
    virtual             ~Context();


    cl_context          context;
    cl_device_id        device;
    cl_command_queue    queue;
};

#endif /* CONTEXT_H_ */
