#include "shared.cl"

constant float  INTERVAL_SIZE   = 1.0f;

constant float  PI_2            = 6.283185307f;

constant float2 ZERO_OFFSET     = (float2)(0.0f, 0.0f);

constant uint   BUCKET_ENTRIES  = BUCKET_ENTRIES_DEFINITION;



kernel void zeroAgentCounts(global uint* agentCounts)
{
    agentCounts[get_global_id(0)] = 0;
}


kernel void sortAgentsIntoBuckets(global float2*  positions,
                                  const  uint     bufferSideLength,
                                  global uint*    buckets,
                                  global uint*    agentCounts)
{
    size_t index = get_global_id(0);
    
    float2 agentPosition = positions[index];
    
    if (all(agentPosition >= 0.0f))
    {
	    // Compute cell the agent resides in
	                   
	    uint2 agentCell2 = convert_uint2(agentPosition);
	    
	    uint agentCell = agentCell2.x + agentCell2.y * bufferSideLength;
	    
	    uint bucket = agentCell * BUCKET_ENTRIES;
	    
	    // Increment agent counter for this cell and retrieve old count
	    
	    uint oldCount = atomic_inc(&agentCounts[agentCell]);
	
	   
	    // If the bucket is not full
	    
	    if (oldCount < BUCKET_ENTRIES)
	    {
	        // Write the agent's index into the bucket
	        
	        buckets[bucket + oldCount] = index;
	    }
    }
}


kernel void resolveCollisions(  global float2* positions,
                                global float*  radii,
                                global uint*   ids,
                                const  uint    count,
                                global uint*   buckets,
                                global uint*   agentCounts,
                                const  uint    bufferSideLength,
                                const  float   maximumRadius,
                                global float4* potentials)
{
    size_t index = get_global_id(0);
    
    float2 agentPosition = positions[index];
    
    if (all(agentPosition >= 0.0f))
    {   
	    uint group = ID_GROUP_MASK & ids[index];
	    
	    float radius = radii[index];
	        
	    float maximumDiameter = maximumRadius + maximumRadius;
	    float maximumDiameterSquared = maximumDiameter * maximumDiameter;
	    
	    float2 offset = ZERO_OFFSET;
	     
	    
	    // Process rectangular cell area around agent cell
	    
	    int2 agentCell = convert_int2_rtn(agentPosition);
	       
	   
	    int additionalCellCount = (int) ceil(maximumDiameter / INTERVAL_SIZE);
	    
	    // Bounds are inclusive
	    
	    int lowerBoundX = max(agentCell.x - additionalCellCount, 0);
	    int upperBoundX = min(agentCell.x + additionalCellCount, bufferSideLength - 1);
	
	    int lowerBoundY = max(agentCell.y - additionalCellCount, 0);
	    int upperBoundY = min(agentCell.y + additionalCellCount, bufferSideLength - 1);  
	
	    //
	    // Iterate over buckets around agent's bucket and resolve collisions
	    //
	    
	    for (int y = lowerBoundY; y <= upperBoundY; y++)
	    {
	        for (int x = lowerBoundX; x <= upperBoundX; x++)
	        {
	            
	            int cell = y * bufferSideLength + x;
	            int bucketIndex = cell * BUCKET_ENTRIES;
	            
	            int agentCount = min( agentCounts[cell], BUCKET_ENTRIES );
	
	            for (int i = 0; i < agentCount; i++)
	            {
	                uint otherAgent = buckets[bucketIndex + i];
	                
	                // If this is not our own entry in the bucket
	                
	                if ( otherAgent != index )
	                {
	                    float2 otherAgentPosition = positions[otherAgent];
	                    float2 difference = agentPosition - otherAgentPosition;
	                    
	                    bool isOneNotZero = (difference.x != 0.0f) || (difference.y != 0.0f);
	                        
	                    if ( isOneNotZero )
	                    {                    
	                        float distanceSquared = difference.x * difference.x + difference.y * difference.y;
	                        
	                        if (distanceSquared < maximumDiameterSquared)
	                        {
	                            float radiiSum = radii[otherAgent] + radius;
	                            
	                            float radiiSumSquared = radiiSum * radiiSum;
	                            
	                            if (distanceSquared < radiiSumSquared)
	                            {
	                                float distance = native_sqrt(distanceSquared);
	                                
	                                float2 direction = difference / distance;
	                                
	                                //
	                                // Check if the agent is about to be pushed into a wall by this agent
	                                //
	                                
	                                float offsetDistance = (radiiSum - distance) * 0.5f;
	                                            
	                                float2 samplePosition = agentPosition + direction * (offsetDistance + radius);
	                                int2 gridPosition = convert_int2_rtn(samplePosition);
	    
	                                float potential = getPotentialInfinity(group, gridPosition, bufferSideLength, potentials);
	                           
	                                bool canPushForThisAgent = !isinf(potential);
	                                
	                                float2 agentOffset = direction * offsetDistance;
	                                
	                                //
	                                // Check if offset sum for all involved agents would put agent into wall
	                                //
	                                
	                                float2 tempOffset = offset + agentOffset;
	                                
	                                gridPosition = convert_int2_rtn(agentPosition + tempOffset);
	                                
	                                potential = getPotentialInfinity(group, gridPosition, bufferSideLength, potentials);
	                                
	                                bool canPushForAllAgents = !isinf(potential);
	                               
	                                bool canSeparate = canPushForThisAgent && canPushForAllAgents;
	                                
	                                // Compute and add offset to agent to resolve collision on our side.
	                                // The other agent will do this itself.
	                                //
	                                // If many many agents overlap then this can add up a huge offset causing
	                                // agents to teleport all over the domain. This showed in the test scenario
	                                // with 256+ agents that started overlapping in a single spot.
	                                // But that is completely an edge case.
	
	                                offset = select(offset, offset + agentOffset, (int2)canSeparate);     
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
	                        
	                        float percentage = (float) index / (float) count;
	                        
	                        float angle = percentage * PI_2;
	                        
	                        float cosine;
	                        float sine = sincos(angle, &cosine);
	            
	                        float2 direction = (float2)(cosine, sine);
	            
	                        // Compute and override offset of agent to resolve collision on our side.
	                        // The other agent will do this itself.
	                        //
	                        // We can't just add up here like below because multiple congruent agents might zero out the offset.
	          
	                        offset = direction * maximumRadius;                 
	                    }
	                }
	            }
	        }
	    }
	
	    // Apply offset to agent
	
	    positions[index] = agentPosition + offset;
	}
}