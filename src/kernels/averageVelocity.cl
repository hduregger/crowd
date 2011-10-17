#include "shared.cl"

kernel void averageVelocity(const uint BUFFER_SIDE_LENGTH, global float4* densityDiscomfortVelocities)
{
    size_t i = get_global_id(0);

    //
    // Inputs:
    //
    // densityDiscomfortVelocity.x  ... sum of density_i
    // densityDiscomfortVelocity.y  ... discomfort (not used here)
    // densityDiscomfortVelocity.zw ... sum of (velocity * density)_i
    //

    float4 densityDiscomfortVelocity = densityDiscomfortVelocities[i];
    
    float  densitySum         = densityDiscomfortVelocity.x;
    float2 velocityDensitySum = densityDiscomfortVelocity.zw;
    float2 averageVelocity;

    if (densitySum != 0.0f)
    {
        // Compute average velocity by dividing weighted velocity sum by density sum
        
        averageVelocity = velocityDensitySum / densitySum;
    }
    else
    {
        averageVelocity = (float2)(0.0f, 0.0f);
    }

    densityDiscomfortVelocities[i].zw = averageVelocity;
}
