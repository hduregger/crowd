#include "shared.cl"

kernel void gradient(const      uint      BUFFER_SIDE_LENGTH,
                     global     float4*   potentials,
                     write_only image2d_t gradients01,
                     write_only image2d_t gradients23)
{
    size_t i = get_global_id(0);

    int2 position = positionFromIndex(i, BUFFER_SIDE_LENGTH);
    
    int2 positionNorth = position;
    int2 positionEast  = position;
    int2 positionSouth = position;
    int2 positionWest  = position;

    positionNorth.y += 1;
    positionEast.x  += 1;
    positionSouth.y -= 1;
    positionWest.x  -= 1;
        
    float4 potentialN = getValueOrInfinity( positionNorth, BUFFER_SIDE_LENGTH, potentials);
    float4 potentialS = getValueOrInfinity( positionSouth, BUFFER_SIDE_LENGTH, potentials);
    float4 potentialW = getValueOrInfinity( positionWest,  BUFFER_SIDE_LENGTH, potentials);
    float4 potential  = getValueOrInfinity( position,      BUFFER_SIDE_LENGTH, potentials);
    float4 potentialE = getValueOrInfinity( positionEast,  BUFFER_SIDE_LENGTH, potentials);

    //
    // Layers 0 and 1
    //
    
    float4 positiveDirection01 = (float4)(potentialE.x, potentialN.x, potentialE.y, potentialN.y);
    float4 negativeDirection01 = (float4)(potentialW.x, potentialS.x, potentialW.y, potentialS.y);
    float4 center01            = (float4)(potential.x,  potential.x,  potential.y,  potential.y);
    
    // Compute gradient against upwind direction (the negative gradient should point along the path to the destination)
    
    int4 isNegativeDirectionSmaller01 = negativeDirection01 <= positiveDirection01;
    
    // Compute forward and backward difference quotient in both x and y
    
    float4 forwardDifferenceQuotient01  = positiveDirection01 - center01;
    float4 backwardDifferenceQuotient01 = center01 - negativeDirection01;
    
    float4 gradient01 = select(forwardDifferenceQuotient01, backwardDifferenceQuotient01, isNegativeDirectionSmaller01);
    
    int4 isInfinityPositiveDirection01 = isinf((float4)(potentialE.x, potentialN.x, potentialE.y, potentialN.y));
    int4 isInfinityNegativeDirection01 = isinf((float4)(potentialW.x, potentialS.x, potentialW.y, potentialS.y));
    
    int4 isInfinity01 = isInfinityPositiveDirection01 && isInfinityNegativeDirection01;
    
    // Mark invalid gradient with zeros
    
    gradient01 = select(gradient01, ZEROS, isInfinity01);

    //
    // Layers 2 and 3
    //
        
    float4 positiveDirection23 = (float4)(potentialE.z, potentialN.z, potentialE.w, potentialN.w);
    float4 negativeDirection23 = (float4)(potentialW.z, potentialS.z, potentialW.w, potentialS.w);
    float4 center23            = (float4)(potential.z,  potential.z,  potential.w,  potential.w);
    
    // Compute gradient against upwind direction (the negative gradient should point along the path to the destination)
    
    int4 isNegativeDirectionSmaller23 = negativeDirection23 <= positiveDirection23;
    
    // Compute forward and backward difference quotient in both x and y
        
    float4 forwardDifferenceQuotient23  = positiveDirection23 - center23;
    float4 backwardDifferenceQuotient23 = center23 - negativeDirection23;
    
    float4 gradient23 = select(forwardDifferenceQuotient23, backwardDifferenceQuotient23, isNegativeDirectionSmaller23);
    
    int4 isInfinityPositiveDirection23 = isinf((float4)(potentialE.z, potentialN.z, potentialE.w, potentialN.w));
    int4 isInfinityNegativeDirection23 = isinf((float4)(potentialW.z, potentialS.z, potentialW.w, potentialS.w));
    
    int4 isInfinity23 = isInfinityPositiveDirection23 && isInfinityNegativeDirection23;
    
    // Mark invalid gradient with zeros
    
    gradient23 = select(gradient23, ZEROS, isInfinity23); 
      
    write_imagef(gradients01, position, gradient01);
    write_imagef(gradients23, position, gradient23);
}

