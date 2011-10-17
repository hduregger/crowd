#include "shared.cl"


/**
 * The cost and speed fields are anisotropic.
 * 
 * NOTE: The components of costNESWs and speedNESWs represent the directions N, E, S, W.
 */

kernel void cost(global float4* densitiesDiscomfortsVelocities,
                 global float4* speedNESWs,
                 global float4* costNESWs,
                 const  float   weightPathLength,
                 const  float   weightTime,
                 const  float   weightDiscomfort,
                 const  int     bufferSideLength )
{
    size_t i = get_global_id(0);

    float4 speedNESW = speedNESWs[i];

    int2 position = (int2)(i % bufferSideLength, i / bufferSideLength);

    float4 discomfortNESW  = getNESWNeighborsYComponentOrInfinity(position, bufferSideLength, densitiesDiscomfortsVelocities);

    // If user passes zero discomfort weight, infinite (wall) discomfort becomes NAN but should be zero instead.
    // Therefore we need to check here.
    
    if (weightDiscomfort == 0.0f)
    {
        discomfortNESW = ZEROS;    
    }
    
    float4 costNESW = (   weightPathLength * speedNESW
                        + (float4)(weightTime, weightTime, weightTime, weightTime)
                        + weightDiscomfort * discomfortNESW )
                      / speedNESW;

    costNESWs[i] = costNESW;
}
