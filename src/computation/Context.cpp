#include "Context.h"


Context::Context(cl_context          context,
                 cl_device_id        device,
                 cl_command_queue    queue)
:   context(context),
    device(device),
    queue(queue)
{
}


Context::~Context()
{
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
}
