#include "shared.cl"

constant float MINIMUM_SPEED       = 0.001f;


/**
 * Returns the speed depending on flow speed, density and maximum allowed speed.
 *
 * Density at agent radius is 0.5, at 2 * r it is 0.0.
 * 
 * NOTE: All parameters represent N, E, S, W directions.
 */

float4 getSpeed(      float4   flowSpeed,
                      float4   density,
               const  float4   MINIMUM_DENSITY,
               const  float4   MAXIMUM_DENSITY,
               const  float4   MAXIMUM_SPEED)
{
    // NOTE: a height map could be sampled here and a topographical speed computed
    //       In our examples everything is flat and we just use the maximum allowed speed.

    float4 topographicalSpeed = MAXIMUM_SPEED;

    float4 mediumSpeed = topographicalSpeed
                        - ( (density - MINIMUM_DENSITY) / (MAXIMUM_DENSITY - MINIMUM_DENSITY) )
                        * (topographicalSpeed - flowSpeed);

    int4 isGreaterEqualMaximum = density >= MAXIMUM_DENSITY;
    int4 isLessEqualMinimum    = density <= MINIMUM_DENSITY;
    
    // Speed in areas with no agents will be maximized even though the flowSpeed is zero.
    // This is because density is zero too. So maximum speed will be chosen.
       
    float4 speed = select(select(mediumSpeed,
                                 topographicalSpeed,
                                 isLessEqualMinimum),
                          flowSpeed,
                          isGreaterEqualMaximum );
    return speed;
}

/**
 * The speed field is anisotropic.
 * 
 * NOTE: The components of speedNESWs represent the directions N, E, S, W.
 */

kernel void speed(const  uint    BUFFER_SIDE_LENGTH,
                  global float4* densitiesDiscomfortsVelocities,
                  global float4* speedNESWs,
                  const  float   MINIMUM_DENSITY,
                  const  float   MAXIMUM_DENSITY,
                  const  float   MAXIMUM_SPEED)
{
    size_t i = get_global_id(0);

    int2 position = (int2)(i % BUFFER_SIDE_LENGTH, i / BUFFER_SIDE_LENGTH);
    
    // x component of density is density sum
    
    float4 densityNESW = getNESWNeighborsXComponentOrInfinity(position, BUFFER_SIDE_LENGTH, densitiesDiscomfortsVelocities);

    float4 flowSpeedNESW;
    
    //
    // Flow speed is the dot product between the general direction and the average velocity vector in the neighboring
    // grid cell in that direction, clamped to positive.
    // e.g. flowSpeed.x = dot( averageVelocityNorth, (float2)( 0.0f,  1.0f) )
    // So the dot product just extracts the component in that direction, which allows us to by-pass the dot product
    // and access the component directly.
    //
    // In areas where no agent contributed density or averageVelocity, both will be zero. So the speed would be zero
    // too. But instead it will be maximized in the speed computation further down below, because density is also zero.
    //
    // In areas where the average velocities of multiple agents result in zero (they cancel each other) density
    // will not be zero. Still it is fine to get resulting low speed depending on the potential because
    // the agents are facing and blocking each other.
    //
    
    int2 positionNorth = position;
    int2 positionEast  = position;
    int2 positionSouth = position;
    int2 positionWest  = position;

    positionNorth.y += 1;
    positionEast.x  += 1;
    positionSouth.y -= 1;
    positionWest.x  -= 1;
    
    flowSpeedNESW.x =  getValueOrZero(positionNorth, BUFFER_SIDE_LENGTH, densitiesDiscomfortsVelocities).w;
    flowSpeedNESW.y =  getValueOrZero(positionEast,  BUFFER_SIDE_LENGTH, densitiesDiscomfortsVelocities).z;
    flowSpeedNESW.z = -getValueOrZero(positionSouth, BUFFER_SIDE_LENGTH, densitiesDiscomfortsVelocities).w;
    flowSpeedNESW.w = -getValueOrZero(positionWest,  BUFFER_SIDE_LENGTH, densitiesDiscomfortsVelocities).z;

    // Enforce a minimum speed to prevent infinite costs, potentials and therefore gradients.
    // This also provides the clamp to positive given in the paper.
    
    flowSpeedNESW = fmax(flowSpeedNESW, (float4)(MINIMUM_SPEED, MINIMUM_SPEED, MINIMUM_SPEED, MINIMUM_SPEED));

    float4 speedNESW = getSpeed( flowSpeedNESW,
                                 densityNESW,
                                 (float4)(MINIMUM_DENSITY, MINIMUM_DENSITY, MINIMUM_DENSITY, MINIMUM_DENSITY),
                                 (float4)(MAXIMUM_DENSITY, MAXIMUM_DENSITY, MAXIMUM_DENSITY, MAXIMUM_DENSITY),
                                 (float4)(MAXIMUM_SPEED,   MAXIMUM_SPEED,   MAXIMUM_SPEED,   MAXIMUM_SPEED) ); 
           

    
    
    speedNESWs[i] = speedNESW;
}
