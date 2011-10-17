#ifndef STATES_H_
#define STATES_H_

namespace FieldRenderState
{
    enum State
    {
        DISCOMFORT          = 0,
        DENSITY             = 1,
        AVERAGE_VELOCITY    = 2,
        SPEED               = 3,
        COST                = 4,
        POTENTIAL           = 5,
        GRADIENT            = 6
    };
}

namespace AgentGroupRenderState
{
    enum State
    {
        GROUP0              = 0,
        GROUP1              = 1,
        GROUP2              = 2,
        GROUP3              = 3
    };
}

namespace DirectionRenderState
{
    enum State
    {
        NORTH               = 0,
        EAST                = 1,
        SOUTH               = 2,
        WEST                = 3
    };
}

namespace UpdateState
{
    enum State
    {
        ALL               = 0,
        SELECTIVELY       = 1
    };
}


#endif /* STATES_H_ */
