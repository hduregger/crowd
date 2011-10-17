constant uint   KEY_MASK        = 0xfff00000;
constant uint   INDEX_MASK      = 0x000fffff;

constant uint   INDEX_BITS      = 20;

constant float  INTERVAL_SIZE   = 1.0f;

constant float  PI_2            = 6.283185307f;

constant float2 ZERO_OFFSET     = (float2)(0.0f, 0.0f);

constant uint   BUCKET_ENTRIES  = BUCKET_ENTRIES_DEFINITION;


float2 getOffset(   const  uint        otherKey,
                    global float4*     agents,
                    const  uint        count,
                    const  float       radius,
                    const  float       diameter,
                    const  float       diameterSquared,
                    const  float2      agentPosition,
                    const  uint        agentIndex,
                    global float4*     potentials,
                    const  uint        bufferSideLength)
{
    uint otherIndex = otherKey & INDEX_MASK;
    
    float2 otherPosition = agents[otherIndex].xy;

    float2 difference = agentPosition - otherPosition;
    
    
    float2 offset = ZERO_OFFSET;
    
    
    bool isOneNotZero = (difference.x != 0.0f) || (difference.y != 0.0f);
    
    if ( isOneNotZero )
    {
        float distanceSquared = difference.x * difference.x + difference.y * difference.y;

         // If agents overlap
         
         bool isLess = distanceSquared < diameterSquared;

         if (isLess)
         {
             // Compute normalize direction

             float distance = native_sqrt(distanceSquared);

             float2 direction = difference / distance;

             //
             // Check if the agent is about to be pushed into a wall
             //
                         
             float2 samplePosition = agentPosition + direction * ((diameter - distance + radius) * 0.5f);
             int2 gridPosition = (int2)( floor(samplePosition.x), floor(samplePosition.y) );

             float potential;
             
             // TODO concept of wall per agent group? does that make sense
             
             float4 potentialsAtPosition = getAbsValueAtPixelInfinity(gridPosition, bufferSideLength, potentials);
             
             if (agentIndex < count * 0.25f)
             {
                 potential = potentialsAtPosition.x;
             }
             else if (agentIndex < count * 0.5f)
             {
                 potential = potentialsAtPosition.y;
             }
             else if (agentIndex < count * 0.75f)
             {
                 potential = potentialsAtPosition.z;
             }
             else
             {
                 potential = potentialsAtPosition.w;
             }
             
             bool wouldPushIntoWall = isinf(potential) || isnan(potential);
             
             if (!wouldPushIntoWall)
             {
                 // Compute and add offset to agent to resolve collision on our side.
                 // The other agent will do this itself.
                 //
                 // If many many agents overlap then this can add up a huge offset causing
                 // agents to teleport all over the domain. This showed in the test scenario
                 // with 256+ agents that started overlapping in a single spot which is totally an
                 // edge case.
                 
                 
                 offset = direction * ((diameter - distance) * 0.5f);
             }
         }
    }
    else
    {
        //
        // Resolve agents in same spot
        // 
        // Because we can't access the other agent here we have to make sure
        // that both agents are offset into different directions some other way.
        //
        // We can use a unique offset for each agent.
        //
        
        float percentage = (float) agentIndex / (float) count;
        
        float angle = percentage * PI_2;
        
        float cosine;
        float sine = sincos(angle, &cosine);

        float2 direction = (float2)(cosine, sine);

        // Compute and override offset of agent to resolve collision on our side.
        // The other agent will do this itself.
        //
        // We can't just add up here like below because multiple congruent agents might zero out the offset.

        offset = direction * radius;         
    }
    
    return offset;
}


kernel void zeroAgentCounts(global uint* agentCounts)
{
    agentCounts[get_global_id(0)] = 0;
}


kernel void computeOffsets( global float4*  agents,
                            global float2*  offsets,
                            global uint*    keys,
                            const  float    radius,
                            const  uint     count,
                            global float4*  potentials,
                            const  uint     bufferSideLength,
                            global float4*  cellArrays,
                            global uint*    agentCounts)
{
    
// Filling buckets with atomic counters version
   
    size_t globalId = get_global_id(0);
    
    float2 agentPosition = agents[globalId].xy;
    
    // Compute cell the agent resides in
                   
    uint agentCell =   ((uint) floor(agentPosition.x))
                     + ((uint) floor(agentPosition.y)) * bufferSideLength;
    
    uint bucket = agentCell * BUCKET_ENTRIES;
    
    // Increment agent counter for this cell and retrieve old count
    
    uint oldCount = atomic_inc(&agentCounts[agentCell]);

   
    // If the bucket is not full
    
    if (oldCount < BUCKET_ENTRIES)
    {
        // Write our position and id into bucket

        cellArrays[bucket + oldCount] = (float4)(agentPosition.x, agentPosition.y, globalId, 0.0f);
    }
   
    
/*
// Filling buckets brute force version
    size_t globalId = get_global_id(0);
    size_t localId  = get_local_id(0);
    
    size_t indexOfArray = globalId * BUCKET_ENTRIES;
    
    uint   agentCount   = 0;

    local float4 localAgents[256];
    
    // Bring agents into local memory in waves
    
    uint loopCount = count / 256;
        
    for (uint i = 0; i < loopCount; i++)
    {
        localAgents[localId] = agents[256 * i + localId];
        
        barrier(CLK_LOCAL_MEM_FENCE);
        
        // Process agents in local memory
                
        for (uint j = 0; j < 256; j++)
        {
            if (agentCount >= BUCKET_ENTRIES)
            {
                break;
            }
            
            float4 localAgentPosition = (float4)(localAgents[j].x, localAgents[j].y, 0.0f, 0.0f);
            
            // If agent is in area
            
            if ((localAgentPosition.x > 0.0f) && (localAgentPosition.y > 0.0f))
            {
                // Compute cell the agent resides in
                
                uint localAgentCellIndex =   ((uint) floor(localAgentPosition.x))
                                           + ((uint) floor(localAgentPosition.y)) * bufferSideLength;
                
                // If we are the agent cell
                
                if (localAgentCellIndex == globalId)
                {
                    // Write agent position into bucket
                    
                    cellArrays[indexOfArray + agentCount] = localAgentPosition;
                    
                    agentCount++;
                }
            }
   
        }
        
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    // If our bucket is not full
    
    if (agentCount < BUCKET_ENTRIES)
    {
        // Write end marker
        
        cellArrays[indexOfArray + agentCount] = (float4)(-1.0f, -1.0f, 0.0f, 0.0f);
    }
*/    
  /*  

// Precomputing offsets version
    
    int i = get_global_id(0);
    
    uint agentKey = keys[i];

    uint agentIndex = agentKey & INDEX_MASK;
    uint agentHash  = (agentKey & KEY_MASK) >> INDEX_BITS;

    float2 agentPosition = agents[agentIndex].xy;

    // Ignore agents outside of area (e.g. parking position)
    
    bool isLess = (agentPosition.x < 0.0f) || (agentPosition.y < 0.0f);

    if ( isLess )
    {
        offsets[agentIndex] = ZERO_OFFSET;

        return;
    }

    float diameter = radius + radius;
    float diameterSquared = diameter * diameter;

    uint additionalIntervalCount = (uint) ceil(diameter / INTERVAL_SIZE);

    float2 offset = ZERO_OFFSET;

    //
    // Check all previous agents until abort
    //

    uint lowerHashBound = agentHash - additionalIntervalCount;

    for (int j = i - 1; j >= 0; j--)
    {
        uint otherKey = keys[j];

        uint hash = (otherKey & KEY_MASK) >> INDEX_BITS;

        // If agent lies in hash interval that is too low, abort
        
        bool isLess = hash < lowerHashBound;

        if (isLess)
        {
            break;
        }

        offset += getOffset(otherKey,
                            agents,
                            count,
                            radius,
                            diameter,
                            diameterSquared,
                            agentPosition,
                            agentIndex,
                            potentials,
                            bufferSideLength);
    }

    //
    // Check all following agents until abort
    //

    uint upperHashBound = agentHash + additionalIntervalCount;

    for (int j = i + 1; j < count; j++)
    {
        uint otherKey = keys[j];

        uint hash = (otherKey & KEY_MASK) >> INDEX_BITS;

        // If agent lies in hash interval that is too high, abort
        
        bool isGreater = hash > upperHashBound;

        if (isGreater)
        {
            break;
        }

        offset += getOffset(otherKey,
                            agents,
                            count,
                            radius,
                            diameter,
                            diameterSquared,
                            agentPosition,
                            agentIndex,
                            potentials,
                            bufferSideLength);
    }

    // Write offset

    offsets[agentIndex] = offset;
 */   

}



kernel void resolveCollisions(  global float4* agents,
                                global float2* offsets,
                                global float4* cellArrays,
                                const  uint    bufferSideLength,
                                const  float   radius,
                                global uint*   agentCounts,
                                const  uint    count)
{
// Iterate over buckets version with agent counts per cell
   
    size_t globalId = get_global_id(0);
    
    float2 agentPosition = agents[globalId].xy;
        
    float diameter = radius + radius;
    float diameterSquared = diameter * diameter;
    
    float2 offset = ZERO_OFFSET;
     
    
    // Process rectangular cell area around agent cell
    // TODO change to circular area
    
    int agentCellX = (int) floor(agentPosition.x);
    int agentCellY = (int) floor(agentPosition.y);
     
   
    int additionalCellCount = (int) ceil(diameter / INTERVAL_SIZE);
    
    // Bounds are inclusive
    
    int lowerBoundX = max(agentCellX - additionalCellCount, 0);
    int upperBoundX = min(agentCellX + additionalCellCount, bufferSideLength - 1);

    int lowerBoundY = max(agentCellY - additionalCellCount, 0);
    int upperBoundY = min(agentCellY + additionalCellCount, bufferSideLength - 1);  

    
    for (int y = lowerBoundY; y <= upperBoundY; y++)
    {
        for (int x = lowerBoundX; x <= upperBoundX; x++)
        {
            
            int cell = y * bufferSideLength + x;
            int bucketIndex = cell * BUCKET_ENTRIES;
            
            int agentCount = min( agentCounts[cell], BUCKET_ENTRIES );

            for (int i = 0; i < agentCount; i++)
            {
                float4 otherAgent = cellArrays[bucketIndex + i];
                
                // If this is not our own entry in the bucket
                
                if (( (size_t) otherAgent.z) != globalId )
                {
                    float2 otherAgentPosition = otherAgent.xy;
                    float2 difference = agentPosition - otherAgentPosition;
                    
                    bool isOneNotZero = (difference.x != 0.0f) || (difference.y != 0.0f);
                        
                    if ( isOneNotZero )
                    {
                    
                        float distanceSquared = difference.x * difference.x + difference.y * difference.y;
                        
                        if (distanceSquared <= diameterSquared)
                        {
                            float distance = native_sqrt(distanceSquared);
                            
                            float2 direction = difference / distance;
                            
                            offset += direction * ((diameter - distance) * 0.5f);
                        }
                    }
                    else
                    {
                        //
                        // Resolve agents in same spot
                        // 
                        // Because we can't access the other agent here we have to make sure
                        // that both agents are offset into different directions some other way.
                        //
                        // We can use a unique offset for each agent.
                        //
                        
                        float percentage = (float) globalId / (float) count;
                        
                        float angle = percentage * PI_2;
                        
                        float cosine;
                        float sine = sincos(angle, &cosine);
            
                        float2 direction = (float2)(cosine, sine);
            
                        // Compute and override offset of agent to resolve collision on our side.
                        // The other agent will do this itself.
                        //
                        // We can't just add up here like below because multiple congruent agents might zero out the offset.
          
                        offset = direction * radius;                 
                    }
                }
            }
        }
    }

    // Apply offset to agent

    agents[globalId].xy = agentPosition + offset;
  
// Iterating over bucket content version
 /*  
    size_t i = get_global_id(0);
    
    float2 agentPosition = agents[i].xy;
    
    float2 offset = ZERO_OFFSET;
     
    uint agentCellIndex =   ((uint) floor(agentPosition.x))
                          + ((uint) floor(agentPosition.y)) * bufferSideLength;
    
    uint bucketIndex = agentCellIndex * BUCKET_ENTRIES;
    
    float diameter = radius + radius;
    float diameterSquared = diameter * diameter;
    
    
    for (uint j = bucketIndex; j < bucketIndex + BUCKET_ENTRIES; j++)
    {
        float2 otherAgentPosition = cellArrays[j].xy;
        
        if (otherAgentPosition.x < 0.0f)
        {
            break;
        }
        
        float2 difference = agentPosition - otherAgentPosition;
        
        float distanceSquared = difference.x * difference.x + difference.y * difference.y;
        
        if (distanceSquared <= diameterSquared)
        {
            float distance = native_sqrt(distanceSquared);
            
            float2 direction = difference / distance;
            
            offset += direction * ((diameter - distance) * 0.5f);
        }
    }
    

    float2 newAgentPosition = agentPosition + offset;

    // Apply offset to agent

    agents[i].xy = newAgentPosition;
  */
/*   
// Applying precomputed offsets version
    size_t i = get_global_id(0);

    float2 agentPosition = agents[i].xy;

    float2 newAgentPosition = agentPosition + offsets[i];

    // Apply offset to agent

    agents[i].xy = newAgentPosition;
*/    
}


// TODO
// Should be brute force offset computation but doesn't work somehow.
// Limiting offset count did not fix it.
// Still a lot slower though.
/*
kernel void computeOffsets( global float4*  agents,
                            global float2*  offsets,
                            global uint*    keys,
                            const  float    radius,
                            const  uint     count,
                            global float4*  potentials,
                            const  uint     bufferSideLength,
                            global float4*  cellArrays,
                            global uint*    agentCounts)
{
    size_t globalId = get_global_id(0);
    size_t localId  = get_local_id(0);

    float2 offset = ZERO_OFFSET;
    
    local float4 localAgents[256];
    
    float2 agentPosition = agents[globalId].xy;
    
    float diameter = radius + radius;
    float diameterSquared = diameter * diameter;
    
    // Bring agents into local memory in waves
    
    uint loopCount = count / 256;
        
    for (uint i = 0; i < loopCount; i++)
    {
        localAgents[localId] = agents[256 * i + localId];
        
        barrier(CLK_LOCAL_MEM_FENCE);
        
        // Process agents in local memory
        
        for (uint j = 0; j < 256; j++)
        {
            float4 localAgent = localAgents[j];
            
            float2 difference = agentPosition - localAgent.xy;
            
            float distanceSquared = difference.x * difference.x + difference.y * difference.y;
            
            if (distanceSquared <= diameterSquared)
            {
                float distance = native_sqrt(distanceSquared);
                
                float2 direction = difference / distance;
                
                offset += direction * ((diameter - distance) * 0.5f);
            }
        }
        
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    // Write offset

    offsets[globalId] = offset;
}
*/
