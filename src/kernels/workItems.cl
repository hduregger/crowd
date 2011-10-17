#include "shared.cl"

kernel void workItems( const uint BUFFER_SIDE_LENGTH, const uint WORK_GROUP_SIDE_LENGTH, global float* workGroupOut)
{
    // Compute global coordinates based on group id
    // NOTE: computed own coordinates because of possible AMD bug (probably fixed now)

    size_t iGlobalGroupBase = getIGlobalGroupBase(WORK_GROUP_SIDE_LENGTH);

    size_t localX = getLocalX(WORK_GROUP_SIDE_LENGTH);
    size_t localY = getLocalY(WORK_GROUP_SIDE_LENGTH);

    size_t globalBaseX = getGlobalBaseX(WORK_GROUP_SIDE_LENGTH, BUFFER_SIDE_LENGTH);
    size_t globalBaseY = getGlobalBaseY(WORK_GROUP_SIDE_LENGTH, BUFFER_SIDE_LENGTH);

    size_t xGlobal = globalBaseX + localX;
    size_t yGlobal = globalBaseY + localY;

    size_t iGlobal = xGlobal + yGlobal * BUFFER_SIDE_LENGTH;

    float v;

    if ( ( (iGlobal % 2)  ) != ( ((iGlobal / BUFFER_SIDE_LENGTH) % 2)  ) )
    {
        v = 0.0f;
    }
    else
    {
        v = 1.0f;
    }

    workGroupOut[iGlobal] = v;
}
