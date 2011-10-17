#include "shared.cl"

#define    EPSILON                            0.001f


constant float4 EPSILONS = (float4)(EPSILON, EPSILON, EPSILON, EPSILON);

#define    GROUP_STATE_SLEEP                  0
#define    GROUP_STATE_IS_CONVERGED           1
#define    GROUP_STATE_UPDATE                 2

#define    UPDATE_METHOD_UPDATE_ALL           0
#define    UPDATE_METHOD_UPDATE_SELECTIVELY   1


/**
 * Initialize start tile states.
 * 
 * The 4 components of potential represent the potential fields of each of the 4 agent groups.
 */

kernel void initialize(const  uint    BUFFER_SIDE_LENGTH,
                       global float4* potentials,
                       global int*    baseGroupStatesOut,
                       local  int*    isInfinitiesScratch)
{
    size_t globalId = get_global_id(0) + get_global_id(1) * get_global_size(0);
    size_t localId  = get_local_id(0)  + get_local_id(1)  * get_local_size(0);
    size_t groupId  = get_group_id(0)  + get_group_id(1)  * get_num_groups(0);

    int4 isZeros = potentials[globalId] == ZEROS;

    //
    // Determine tile start state
    //
    
    int isInfinity = !any(isZeros);
    
    isInfinitiesScratch[localId] = isInfinity;
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    int isGroupInfinity = reduceAnd(isInfinitiesScratch, localId, get_local_size(0) * get_local_size(1));
    
    if (localId == 0)
    {
        if (isGroupInfinity)
        {
            // Let completely infinite tile sleep
            
            baseGroupStatesOut[groupId] = GROUP_STATE_SLEEP;
        }
        else
        {
            // Update this group because it contains elements that are not infinite
            
            baseGroupStatesOut[groupId] = GROUP_STATE_UPDATE;
        }
    }
}

/**
 * "A fast sweeping method..." gives the more complicated solution with the root term as backup solution.
 * TODO maple solve wrong?
 * 
 * Solving the equation (x - a)^+^2 + (x - b)^+^2 = h^2 with Maple gives the simpler solutions c + a or c + b.
 * "A fast sweeping method..." solution for 2d gives nice result.
 * 
 * (x)^+ = max(x, 0)
 */

float4 solveQuadratic(float4 potentialX, float4 potentialY, float4 cost)
{
    float4 solution;

    float4 potentialMin = fmin(potentialX, potentialY);
    
    float4 difference = potentialX - potentialY;
    float4 absoluteDifference = fabs(difference);
    
    float4 costSquared = cost * cost;
    
    float4 solutionA  = potentialMin + cost;
    float4 solutionB = ( potentialX + potentialY + native_sqrt(costSquared + costSquared - difference * difference) ) * 0.5f;
    
    int4 isGreaterEqual = absoluteDifference >= cost;
    solution = select( solutionB, solutionA, isGreaterEqual );

    return solution;
}

/**
 * Does it like "A fast sweeping method..."
 */


float4 computeSimple(float4 potential,
                     float4 potentialN, float4 potentialS, float4 potentialW, float4 potentialE,
                     float4 costN, float4 costS, float4 costW, float4 costE)
{
    int4 isLessThanWE = (potentialW + costW) <= (potentialE + costE);

    float4 potentialX  = select(potentialE,  potentialW,  isLessThanWE);
    float4 costX = select(costE, costW, isLessThanWE);
    
    int4 isLessThanSN = (potentialS + costS) <= (potentialN + costN);
    
    float4 potentialY  = select(potentialN,  potentialS,  isLessThanSN);
    float4 costY = select(costN, costS, isLessThanSN);

    float4 cost = costX + costY;

    float4 solution;

    solution = solveQuadratic(potentialX, potentialY, cost);

    // Should be decreasing or same
  
    solution = fmin(solution, potential);

    return solution;
}


int smallStep(const   uint    BUFFER_SIDE_LENGTH,
              const   uint    WORK_GROUP_SIDE_LENGTH,
              global  float4 const* restrict costNESWs,
              global  float4* potentials,
              local   float2* potentialsScratch,
              local   int*    isRequiringUpdatesScratch,
              size_t          groupId)
{
    size_t globalX = get_global_id(0);
    size_t globalY = get_global_id(1);
    
    size_t globalI = globalX + globalY * BUFFER_SIDE_LENGTH;
    
    //
    // Compute local coordinates in scratch memory that has 1 additional row and column at the top, bottom, left and right.
    //
    
    size_t localX = get_local_id(0);
    size_t localY = get_local_id(1);
    
    size_t localX2 = localX + 1;
    size_t localY2 = localY + 1;
    
    size_t localSize = WORK_GROUP_SIDE_LENGTH + 2;
    
    size_t localI  = localX2 + localY2 * localSize;
    
    size_t localIW = localI - 1;
    size_t localIE = localI + 1;
    size_t localIS = localI - localSize;
    size_t localIN = localI + localSize;
    
    //
    // Initialize local elements inside work group
    //
    
    float4 originalPotential = potentials[globalI];
    
    size_t localSizeSquared = localSize * localSize;
    
    // Write xy values sequentially into buffer, then zw values.
    
    local float2* potentialLocalXY =  potentialsScratch;
    local float2* potentialLocalZW = &potentialsScratch[localSizeSquared];
    
    potentialLocalXY[localI] = originalPotential.xy;
    potentialLocalZW[localI] = originalPotential.zw;
    
    //
    // Initialize local elements outside work group (local border)
    //
    
    if (localX2 == 1)
    {
        float4 temporary = getValueOrInfinity((int2)(globalX - 1, globalY), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIW] = temporary.xy;
        potentialLocalZW[localIW] = temporary.zw;
    }
    
    if (localX2 == (localSize - 2))
    {
        float4 temporary = getValueOrInfinity((int2)(globalX + 1, globalY), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIE] = temporary.xy;
        potentialLocalZW[localIE] = temporary.zw;
    }
    
    if (localY2 == 1)
    {
        float4 temporary = getValueOrInfinity((int2)(globalX, globalY - 1), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIS] = temporary.xy;
        potentialLocalZW[localIS] = temporary.zw;
    }
    
    if (localY2 == (localSize - 2))
    {
        float4 temporary = getValueOrInfinity((int2)(globalX, globalY + 1), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIN] = temporary.xy;
        potentialLocalZW[localIN] = temporary.zw;
    }
    
    // Prepare cost vectors for vectorized computation over all 4 agent layers
    
    float4 costNESW = costNESWs[globalI];
    
    float4 costN = costNESW.x;
    float4 costE = costNESW.y;
    float4 costS = costNESW.z;
    float4 costW = costNESW.w;
    
    float4 solution = originalPotential;
    
    float4 potentialN;
    float4 potentialS;
    float4 potentialW;
    float4 potentialE;
    
    float4 potential;
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    potential = solution;
    
    potentialN.xy = potentialLocalXY[localIN];
    potentialN.zw = potentialLocalZW[localIN];
    potentialS.xy = potentialLocalXY[localIS];
    potentialS.zw = potentialLocalZW[localIS];
    potentialW.xy = potentialLocalXY[localIW];
    potentialW.zw = potentialLocalZW[localIW];
    potentialE.xy = potentialLocalXY[localIE];
    potentialE.zw = potentialLocalZW[localIE];
    
    solution = computeSimple(potential, potentialN, potentialS, potentialW, potentialE, costN, costS, costW, costE);
    
    potentials[globalI] = solution;
    
    //
    // Compute item state
    //
    
    float4 newPotential = solution;
    
    int4 isRequiringUpdates = (fabs(originalPotential - newPotential) > EPSILONS);
    int  isRequiringUpdate  = any(isRequiringUpdates);
    
    size_t localId = localX + localY * WORK_GROUP_SIDE_LENGTH;
    
    isRequiringUpdatesScratch[localId] = isRequiringUpdate;
    
    //
    // Compute group state
    //
    
    barrier(CLK_LOCAL_MEM_FENCE);
    
    int isGroupRequiringUpdate = reduceOr(isRequiringUpdatesScratch, localId, get_local_size(0) * get_local_size(1));
    
    return isGroupRequiringUpdate;
}


void largeStep( const   uint    BUFFER_SIDE_LENGTH,
                const   uint    WORK_GROUP_SIDE_LENGTH,
                global  float4 const* restrict costNESWs,
                global  float4* potentials,
                local   float2* potentialsScratch,
                const   uint    loopCount,
                local   int*    isConvergedsScratch,
                global  int*    groupStatesOut,
                size_t          groupId,
                const   int     updateMethod)
{
    size_t globalX = get_global_id(0);
    size_t globalY = get_global_id(1);
    
    size_t globalI = globalX + globalY * BUFFER_SIDE_LENGTH;

    //
    // Compute local coordinates in scratch memory that has 1 additional row and column at the top, bottom, left and right.
    //
    
    size_t localX = get_local_id(0);
    size_t localY = get_local_id(1);
    
    size_t localX2 = localX + 1;
    size_t localY2 = localY + 1;
    
    size_t localSize = WORK_GROUP_SIDE_LENGTH + 2;
    
    size_t localI  = localX2 + localY2 * localSize;
    
    size_t localIW = localI - 1;
    size_t localIE = localI + 1;
    size_t localIS = localI - localSize;
    size_t localIN = localI + localSize;
    
    //
    // Initialize local elements inside work group
    //
    
    float4 originalPotential = potentials[globalI];
    
    size_t localSizeSquared = localSize * localSize;
    
    // Write xy values sequentially into buffer, then zw values.
    
    local float2* potentialLocalXY =  potentialsScratch;
    local float2* potentialLocalZW = &potentialsScratch[localSizeSquared];
    
    potentialLocalXY[localI] = originalPotential.xy;
    potentialLocalZW[localI] = originalPotential.zw;
    
    //
    // Initialize local elements outside work group (local border)
    //
    
    if (localX2 == 1)
    {
        float4 temporary = getValueOrInfinity((int2)(globalX - 1, globalY), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIW] = temporary.xy;
        potentialLocalZW[localIW] = temporary.zw;
    }
    
    if (localX2 == (localSize - 2))
    {
        float4 temporary = getValueOrInfinity((int2)(globalX + 1, globalY), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIE] = temporary.xy;
        potentialLocalZW[localIE] = temporary.zw;
    }
    
    if (localY2 == 1)
    {
        float4 temporary = getValueOrInfinity((int2)(globalX, globalY - 1), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIS] = temporary.xy;
        potentialLocalZW[localIS] = temporary.zw;
    }
    
    if (localY2 == (localSize - 2))
    {
        float4 temporary = getValueOrInfinity((int2)(globalX, globalY + 1), BUFFER_SIDE_LENGTH, potentials);
        potentialLocalXY[localIN] = temporary.xy;
        potentialLocalZW[localIN] = temporary.zw;
    }
    
    // Prepare cost vectors for vectorized computation over all 4 agent layers
    
    float4 costNESW = costNESWs[globalI];
    
    float4 costN = costNESW.x;
    float4 costE = costNESW.y;
    float4 costS = costNESW.z;
    float4 costW = costNESW.w;
    
    //
    // Iterate on local field
    //
    // We need synchronisation. Without it a single work item might work ahead through
    // all iterations without getting any new information.
    //
    // We don't need ping-pong because it is good for fast information propagation
    // to read an updated neighbor early. Therefore the single buffer version can perform
    // equal or better than the ping-pong version, quality wise. We do lose determinism though.
    //
    
    float4 solution = originalPotential;
    
    float4 potentialN;
    float4 potentialS;
    float4 potentialW;
    float4 potentialE;
    
    float4 potential;
    
    float4 previousPotential;
    
    //
    // Unrolling loop into 2 steps.
    //
    // NOTE: When changing unroll factor update class constant for GUI.
    //

    for (int i = 0; i < loopCount; i++)
    {
        // First iteration
        
        barrier(CLK_LOCAL_MEM_FENCE);
        
        potential = solution;
        
        potentialN.xy = potentialLocalXY[localIN];
        potentialN.zw = potentialLocalZW[localIN];
        potentialS.xy = potentialLocalXY[localIS];
        potentialS.zw = potentialLocalZW[localIS];
        potentialW.xy = potentialLocalXY[localIW];
        potentialW.zw = potentialLocalZW[localIW];
        potentialE.xy = potentialLocalXY[localIE];
        potentialE.zw = potentialLocalZW[localIE];
        
        solution = computeSimple(potential, potentialN, potentialS, potentialW, potentialE, costN, costS, costW, costE);
       
        potentialLocalXY[localI] = solution.xy;
        potentialLocalZW[localI] = solution.zw;
        
        
        // Second iteration
        
        barrier(CLK_LOCAL_MEM_FENCE);
        
        potential = solution;
        
        previousPotential = solution;
        
        potentialN.xy = potentialLocalXY[localIN];
        potentialN.zw = potentialLocalZW[localIN];
        potentialS.xy = potentialLocalXY[localIS];
        potentialS.zw = potentialLocalZW[localIS];
        potentialW.xy = potentialLocalXY[localIW];
        potentialW.zw = potentialLocalZW[localIW];
        potentialE.xy = potentialLocalXY[localIE];
        potentialE.zw = potentialLocalZW[localIE];
      
        solution = computeSimple(potential, potentialN, potentialS, potentialW, potentialE, costN, costS, costW, costE);
        
        potentialLocalXY[localI] = solution.xy;
        potentialLocalZW[localI] = solution.zw;

    }
    
    potentials[globalI] = solution;

    switch (updateMethod)
    {
        case UPDATE_METHOD_UPDATE_SELECTIVELY:
        {
            //
            // Compute item convergence
            //
            
            float4 newPotential = solution;
            
            int4 isConvergeds = (fabs(previousPotential - newPotential) <= EPSILONS) || isinf(newPotential);
            int  isConverged  = all(isConvergeds);
                     
            size_t localId = localX + localY * WORK_GROUP_SIDE_LENGTH;
            
            isConvergedsScratch[localId] = isConverged;
            
            //
            // Compute group convergence
            //
            
            barrier(CLK_LOCAL_MEM_FENCE);
            
            int isGroupConverged = reduceAnd(isConvergedsScratch, localId, WORK_GROUP_SIDE_LENGTH * WORK_GROUP_SIDE_LENGTH);
            
            if (localId == 0)
            {
                if (isGroupConverged == 1)
                {
                    groupStatesOut[groupId] = GROUP_STATE_IS_CONVERGED;
                }
                else
                {
                    groupStatesOut[groupId] = GROUP_STATE_UPDATE;
                }
            }
            
            break;
        }
                
        // UPDATE_METHOD_UPDATE_ALL
        
        default:
        {
            break;
        }
    }
}


bool isNeighborActive(size_t groupX, size_t groupY, size_t groupsPerSide, global int const* restrict groupStatesIn)
{
    int2 N = (int2)(groupX    , groupY + 1);
    int2 S = (int2)(groupX    , groupY - 1);
    int2 E = (int2)(groupX + 1, groupY    );
    int2 W = (int2)(groupX - 1, groupY    );      
    
    int4 state;
    
    state.x = getIntOrZeroRestrict(N, groupsPerSide, groupStatesIn);
    state.y = getIntOrZeroRestrict(S, groupsPerSide, groupStatesIn);
    state.z = getIntOrZeroRestrict(E, groupsPerSide, groupStatesIn);
    state.w = getIntOrZeroRestrict(W, groupsPerSide, groupStatesIn);
    
    bool isActive = !all(state == GROUP_STATE_SLEEP);

    return isActive;
}

/**
 * Compute potential.
 * 
 * The input cost field is anisotropic, its components represent the directions N, E, S, W.
 * 
 * The components of potential represent the 4 agent layers, e.g. there is a potential field
 * for each agent group.
 */

kernel void potential( const   uint    BUFFER_SIDE_LENGTH,
                       const   uint    WORK_GROUP_SIDE_LENGTH,
                       global  float4 const* restrict costNESWs,
                       global  float4* potentialIn,
                       local   float2* potentialLocal,
                       const   uint    loopCount,
                       local   int*    booleansScratch,
                       global  int const* restrict groupStatesIn,
                       global  int*    groupStatesOut,
                       const   int     updateMethod)
{
    size_t groupX = get_group_id(0);
    size_t groupY = get_group_id(1);
    size_t groupsPerSide = get_num_groups(0);
    
    size_t groupId = groupX + groupY * groupsPerSide;
    
    
    switch (updateMethod)
    {
        case UPDATE_METHOD_UPDATE_ALL:
        {
            largeStep(BUFFER_SIDE_LENGTH,
                      WORK_GROUP_SIDE_LENGTH,
                      costNESWs,
                      potentialIn,
                      potentialLocal,
                      loopCount,
                      booleansScratch,
                      groupStatesOut,
                      groupId,
                      updateMethod);
            break;
        }
        
        // UPDATE_METHOD_UPDATE_SELECTIVELY
        
        default:
        {
            local int state;    
            
            bool isFirstWorkItem = (get_local_id(0) + get_local_id(1)) == 0;
            
            if (isFirstWorkItem)
            {
                state = groupStatesIn[groupId];
            }
            
            barrier(CLK_LOCAL_MEM_FENCE);
        
                
            switch (state)
            {
                case GROUP_STATE_IS_CONVERGED:
                case GROUP_STATE_SLEEP:
                {
                    local bool doWakeUp;
          
                    if (isFirstWorkItem)
                    {
                        // If any neighbor is active, wake up so that we are updated in the next step,
                        // else keep sleeping.
                        
                        doWakeUp = isNeighborActive(groupX, groupY, groupsPerSide, groupStatesIn);                        
                    }
                    
                    barrier(CLK_LOCAL_MEM_FENCE);
                        
                    if (doWakeUp)
                    {
                        // Check if tile needs an update
                        
                        int isGroupRequiringUpdate = smallStep(BUFFER_SIDE_LENGTH,
                                                               WORK_GROUP_SIDE_LENGTH,
                                                               costNESWs,
                                                               potentialIn,
                                                               potentialLocal,
                                                               booleansScratch,
                                                               groupId);
                        if (isGroupRequiringUpdate == 1)
                        {
                            // Update tile
                           
                            largeStep(BUFFER_SIDE_LENGTH,
                                      WORK_GROUP_SIDE_LENGTH,
                                      costNESWs,
                                      potentialIn,
                                      potentialLocal,
                                      loopCount,
                                      booleansScratch,
                                      groupStatesOut,
                                      groupId,
                                      updateMethod);
                        }
                        else
                        {
                            if (isFirstWorkItem)
                            {
                                groupStatesOut[groupId] = GROUP_STATE_SLEEP;
                            }
                        }
                    }
                    else
                    {
                        if (isFirstWorkItem)
                        {
                            groupStatesOut[groupId] = GROUP_STATE_SLEEP;
                        }
                    }
                    
                    break;
                }
                
                // GROUP_STATE_UPDATE
                
                default:
                {
                    largeStep(BUFFER_SIDE_LENGTH,
                              WORK_GROUP_SIDE_LENGTH,
                              costNESWs,
                              potentialIn,
                              potentialLocal,
                              loopCount,
                              booleansScratch,
                              groupStatesOut,
                              groupId,
                              updateMethod);
        
                    break;
                }
            }
            
            break;
        }
    }

}