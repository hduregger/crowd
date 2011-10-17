#include "shared.cl"

// Negative parking positions so that agents are ignored in collision resolution and in movement update

constant float2     PARKING_POSITION             = (float2)(-1000.0f, -1000.0f);

// agentCounts 0,1,2,3 active, 4,5,6,7 parked

constant int AGENT_COUNT_PARKED_BASE             =  4;

constant float      TURN_RATE_FAST_FACTOR        = 4.0f;
constant float      TURN_RATE_FAST_THRESHOLD     = 0.6f;

constant float      OPPOSITE_DIRECTION_DOT_PRODUCT_THRESHOLD = -0.8f;

#define             EXIT_MODE_PARK         0
#define             EXIT_MODE_CHANGE_GROUP 1
#define             EXIT_MODE_RESPAWN      2



float2 turnToDirection(float2 direction, float2 targetDirection, float dotProduct, float turnRate)
{
    //
    // Slowly turn towards new direction
    //
    
    float2 newDirection;
    
    // If new direction is directly opposite
    
    if (dotProduct < OPPOSITE_DIRECTION_DOT_PRODUCT_THRESHOLD)
    {
        // Compute a direction perpendicular to the current direction. Then compute the offset vector
        // from the current direction to the perpendicular one. Use part of this offset direction
        // to compute a new direction turned a bit towards the perpendicular direction.
        
        float2 orthogonalDirection = (float2)(-direction.y, direction.x);
        
        newDirection = normalize( direction + normalize(orthogonalDirection - direction) * turnRate );
    }
    else
    {
        float2 directionOffset = targetDirection - direction;
        float directionOffsetLength = length(directionOffset);
        
        //
        // Ensure that the agent does not turn faster than the turn rate allows.
        //
        // Covers against zero directionOffsetLength if turnRate is zero or greater.
        //
        
        if (directionOffsetLength > turnRate)
        {
            directionOffset /= directionOffsetLength;
            
            newDirection = normalize( direction + directionOffset * turnRate );
        }
        else
        {
            newDirection = targetDirection;
        }
    }
    
    return newDirection;
}


float getTurnRate(float turnRate, float dotProduct, bool isFacingWall)
{
    //
    // Choose faster turn rate if we are facing a wall or trying to turn around
    //
   
    bool isTurningAround = dotProduct < TURN_RATE_FAST_THRESHOLD; 
    
    bool isTurningFast = isFacingWall || isTurningAround;
        
    turnRate = select(turnRate, turnRate * TURN_RATE_FAST_FACTOR, isTurningFast);
    
    return turnRate;
}


float2 getGradient(uint                group,
                   float2              positionWithOffset,
                   read_only image2d_t gradientIn01,
                   read_only image2d_t gradientIn23,
                   const uint          BUFFER_SIDE_LENGTH)
{ 
    float2 gradient;
    
    // Retrieve gradient for agent group
    
    switch (group)
    {
        case 0:
        {
            gradient = getValueWithBilinearFilteringOrZero(positionWithOffset, BUFFER_SIDE_LENGTH, gradientIn01).xy;
            break;
        }
        
        case 1:
        {
            gradient = getValueWithBilinearFilteringOrZero(positionWithOffset, BUFFER_SIDE_LENGTH, gradientIn01).zw;
            break;
        }
        
        case 2:
        {
            gradient = getValueWithBilinearFilteringOrZero(positionWithOffset, BUFFER_SIDE_LENGTH, gradientIn23).xy;
            break;
        }
        
        case 3:
        {
            gradient = getValueWithBilinearFilteringOrZero(positionWithOffset, BUFFER_SIDE_LENGTH, gradientIn23).zw;
            break;
        }
    }
    
    return gradient;    
}


kernel void move(const  uint         BUFFER_SIDE_LENGTH,
                 read_only image2d_t gradientIn01,
                 read_only image2d_t gradientIn23,
                 global float2*      positions,
                 global float2*      directions,
                 global float*       speeds,
                 global float*       maximumSpeeds,
                 global uint*        ids,
                 global float*       radii,
                 global float*       turnRates,                 
                 global float4*      speedField,
                 const  float        deltaTime,
                 const  int          areaSideLength,
                 global float4*      potentials,
                 const  global int4* entries,
                 const  int          exitMode,
                 global uint*        agentCounts) // 0,1,2,3 groups, 4,5,6,7 parked
{
    size_t i          = get_global_id(0);
    size_t agentCount = get_global_size(0);

    // NOTE: currently retrieving new direction from gradient retrieved
    // at radius offset into current direction and then retrieving
    // speed for the new direction retrieved at the current cell depending
    // on the new direction.
    //
    // This could be bad if we are moving across multiple grid cells per step.
    // And the agent moves in the direction that is actually correct only at the
    // offset position.

    float radius = radii[i];
    
    // Retrieve previous position, direction and velocity

    float2 position  = positions[i];
    float2 direction = directions[i];
    
    uint id = ids[i];
    uint group = ID_GROUP_MASK & id;

    // If agent is not parked

    bool isInsideArea = (position.x >= 0.0f) && (position.y >= 0.0f) && (position.x < areaSideLength) && (position.y < areaSideLength);
    
    if ( isInsideArea )
    {
        int2 gridPosition = convert_int2_rtn(position);
        
        bool isInsideWall = isinf(getPotentialInfinity(group, gridPosition, BUFFER_SIDE_LENGTH, potentials));
        
        // If agent spawned (or ended up in wall which should never happen)
        
        if (isInsideWall)
        {
            // Park it
            
            positions[i] = PARKING_POSITION;
             
            atomic_dec(&agentCounts[                          group]);
            atomic_inc(&agentCounts[AGENT_COUNT_PARKED_BASE + group]);
        }
        else
        {
            // Compute offset for gradient lookup so that we don't retrieve a gradient value
            // influenced by agent itself
    
            float2 offset = direction * radius;
    
            //
            // Compute sample position
            //
    
            float2 positionWithOffset     = position + offset;
            int2   gridPositionWithOffset = convert_int2_rtn(positionWithOffset);
    
            // Lookup gradient
            
            float2 gradient = getGradient(group,
                                          positionWithOffset,
                                          gradientIn01,
                                          gradientIn23,
                                          BUFFER_SIDE_LENGTH);
            
            // Check if the gradient was sampled inside a wall
            
            bool isInsideWall = any(isinf(gradient) || isnan(gradient));
            
            // Check if both components are zero, if so gradient is invalid, from all infinite potentials, or
            // from goal areas.

            bool isInsideInvalidEdge = all(gradient == (float2)(0.0f, 0.0f));
            
            
            //
            // Check if the agent stepped into an exit (0 potential) cell
            //
            
            float potential = getPotentialInfinity(group, gridPositionWithOffset, BUFFER_SIDE_LENGTH, potentials);
                         
            // If agent touches exit
            
            if (potential == 0.0f)
            {
                switch (exitMode)
                {
                    // If it should park, park it.
                    // If it should respawn, park it so that it can respawn next frame.
                
                    case EXIT_MODE_PARK:
                    case EXIT_MODE_RESPAWN:
                    default:
                    {
                        positions[i] = PARKING_POSITION;
                        
                        atomic_dec(&agentCounts[                          group]);
                        atomic_inc(&agentCounts[AGENT_COUNT_PARKED_BASE + group]);
                        
                        break;
                    }
                    
                    // Change its group so that it heads for different exit
                    
                    case EXIT_MODE_CHANGE_GROUP:
                    {
                        atomic_dec(&agentCounts[group]);
                        
                        // Change the group
                        
                        group = (group + 1) % 4;
                        
                        atomic_inc(&agentCounts[group]);
                        
                        // Change only the group bits in the id
                        
                        ids[i] = (~ID_GROUP_MASK & id) | (ID_GROUP_MASK & group);
                               
                        break;
                    }
                }
            }
            else
            {
                //
                // Update agent position, speed and orientation
                //
                
                bool isFacingWall = isInsideWall || isInsideInvalidEdge;
                
                //
                // We are only interested in the direction of the gradient.
                // The new direction points opposite of the gradient.
                // The agent moves against the gradient towards the goal.
                //
                
                float2 targetDirection = -normalize(gradient);
                  
                // If hitting wall, set new direction to negative direction so that we turn around
                
                targetDirection = select(targetDirection, -direction, (int2)isFacingWall);
        
        
                float dotProduct = dot(targetDirection, direction);
                
                // Get the turn rate for current situation 
                
                float turnRate = getTurnRate(turnRates[i], dotProduct, isFacingWall);
        
                
                // Let agent turn towards new direction
                
                float2 newDirection = turnToDirection(direction, targetDirection, dotProduct, turnRate);
                
                
                
                float speed = 0.0f;
        
                // If the agent hit a wall, we want it to turn in place, else compute a speed based on speed field
                
                if (!isFacingWall)
                {
                    //
                    // Retrieve speed based on sample position
                    // and interpolate from the 2 nearest general directions (N, E, S, W).
                    //
            
                    float4 anisotropicSpeeds = getValueOrZero(gridPositionWithOffset, BUFFER_SIDE_LENGTH, speedField);
                    
                    // Pythagoras tells us that for unit vector x * x + y * y = 1. We can use that
                    // to retrieve speed components.
                    
                    float xComponentFactor = newDirection.x * newDirection.x;
                    float yComponentFactor = newDirection.y * newDirection.y;
                    
                    int2 isGreaterThanEqual = newDirection >= 0.0f;
                    
                    // East
                    speed = select(speed, speed + (xComponentFactor * anisotropicSpeeds.y),  isGreaterThanEqual.x);
                    
                    // West
                    speed = select(speed, speed + (xComponentFactor * anisotropicSpeeds.w), !isGreaterThanEqual.x);
                    
                    // North
                    speed = select(speed, speed + (yComponentFactor * anisotropicSpeeds.x),  isGreaterThanEqual.y);
            
                    // South
                    speed = select(speed, speed + (yComponentFactor * anisotropicSpeeds.z), !isGreaterThanEqual.y);
                }
        
                //
                // Limit speed to maximum speed for this agent
                //
                
                speed = fmin(speed, maximumSpeeds[i]);
        
                //
                // Update position and velocity
                //
        
                float2 newVelocity = newDirection * speed;     
                float2 newPosition = position + newVelocity * deltaTime;
                
                // Check if new position is inside a wall
    
                int2 newGridPosition = convert_int2_rtn(newPosition);
                bool isNewPositionInsideWall = isinf(getPotentialInfinity(group, newGridPosition, BUFFER_SIDE_LENGTH, potentials));
                
                // If new position would put agent inside wall, stay put, don't move
                
                newPosition = select(newPosition, position, (int2)isNewPositionInsideWall);
                speed       = select(speed,       0.0f,           isNewPositionInsideWall);
               
                //
                // Write new position, direction and speed
                //
        
                positions[i]    = newPosition;
                directions[i]   = newDirection;
                speeds[i]       = speed;
            }
        }
    }
    else
    {
        //
        // Deal with parked agents
        //
        
        switch (exitMode)
        {
            default:
            {
                break;
            }
            
            // Let agent respawn.
            //
            // We first park a respawning agent to respawn it here, so we can also respawn agents
            // that have been parked because they were located inside a wall.
            
            case EXIT_MODE_RESPAWN:
            {
                int4 entry = entries[group];
                
                int width  = entry.z - entry.x + 1;
                int height = entry.w - entry.y + 1;
                
                // Number of possible spawn locations
                
                int locations = width * height;
                
                // Index into locations depending on global id
                
                int index = i % locations;
                
                // Local position in spawn area
                
                int2 localPosition = positionFromIndex(index, width);
                
                int2 globalPosition = entry.xy + localPosition;
                
                positions[i] = (float2)(globalPosition.x, globalPosition.y);
                
                atomic_dec(&agentCounts[AGENT_COUNT_PARKED_BASE + group]);
                atomic_inc(&agentCounts[                          group]);
                
                break;
            }
        }
    }
}
