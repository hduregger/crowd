// TODO formatting variable naming
// TODO method naming

constant size_t ELEMENTS_PER_WORK_ITEM_SCAN   = 2; // 2 because of binary tree
constant size_t ELEMENTS_PER_WORK_ITEM_OTHERS = 2; // TODO works only with 2 for now (but didn't seem faster with 4)


/**
 * This kernel requires that 1 work item deals with 2 elements
 * because of the binary tree structure.
 */

kernel void prefixSumScan(global uint* elements,
                          const  uint  count,
                          local  uint* temp,
                          global uint* sums,
                          const  uint  doWriteSums,
                          const  uint  bitMask,
                          global uint* prefixSums,
                          const  uint  doWriteTotalFalses,
                          global uint* totalFalses)
{
    size_t i         = get_local_id(0);
    size_t group     = get_group_id(0);
    size_t groupSize = get_local_size(0);

    size_t elementsPerGroup = groupSize * ELEMENTS_PER_WORK_ITEM_SCAN;

    size_t groupOffset = group * elementsPerGroup;

    size_t itemOffset = ELEMENTS_PER_WORK_ITEM_SCAN * i;


    // TODO
    // Do coalesced memory access like
    // http://http.developer.nvidia.com/GPUGems3/gpugems3_ch32.html
    // does?
    // Instead of neighboring items per thread, let all threads access
    // items that are near to each other, and then again at the other end


    // If we are just summing up

    if (bitMask == 0)
    {
        // Sum up elements

        temp[ itemOffset     ] = elements[ groupOffset + itemOffset     ];
        temp[ itemOffset + 1 ] = elements[ groupOffset + itemOffset + 1 ];
    }
    else
    {
        // Count lesser elements

        temp[ itemOffset     ] = !( elements[ groupOffset + itemOffset     ] & bitMask );
        temp[ itemOffset + 1 ] = !( elements[ groupOffset + itemOffset + 1 ] & bitMask );
    }

    int offset = 1;

    size_t binaryOffset = i * 2;

    //
    // Sweep up: Pair-wise sum elements up from leaves towards the root (reduce).
    //           Only half of the items start summing.
    //

    for (int d = elementsPerGroup >> 1; d > 0; d >>= 1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);

        if (i < d)
        {
            int a = offset * ( binaryOffset + 1 ) - 1;
            int b = offset * ( binaryOffset + 2 ) - 1;

            temp[b] += temp[a];
        }

        offset *= 2;
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    if (get_local_id(0) == 0)
    {
        if (doWriteSums)
        {
            // Store sum for exchange with other groups.
            //
            // NOTE: If this is the group covering the last elements
            //       then it will write wrong results when the group contains padding elements.
            //       This is no problem because the sum value of the last group is not used.

            sums[group] = temp[ elementsPerGroup - 1 ];
        }

        // Set last element to zero

        temp[ elementsPerGroup - 1 ] = 0;
    }

    //
    // Sweep down: Propagate partial sums towards leaves starting at root
    //

    for (int d = 1; d < elementsPerGroup; d *= 2) // TODO left shift
    {
         offset >>= 1;

         barrier(CLK_LOCAL_MEM_FENCE);

         if (i < d)
         {
            int a = offset * ( binaryOffset + 1 ) - 1;
            int b = offset * ( binaryOffset + 2 ) - 1;

            uint t  = temp[a];
            temp[a] = temp[b];
            temp[b] += t;
         }
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    //
    // NOTE: This part is only used when the element array fits into
    //       a single work group, so no global synchronisation is required.
    //

    if ( get_global_id(0) == 0 )
    {
        if (doWriteTotalFalses)
        {
            // Add up possible false last element with last prefix sum

            uint lastIndex = count - 1;

            totalFalses[0] = !(elements[ lastIndex ] & bitMask) + temp[ lastIndex ];
        }
    }

    prefixSums[ groupOffset + itemOffset     ] = temp[ itemOffset     ];
    prefixSums[ groupOffset + itemOffset + 1 ] = temp[ itemOffset + 1 ];
}


kernel void addGroupPrefix(global uint* prefixSums,
                           global uint* sums,
                           global uint* elements,
                           const  uint  count,
                           const  uint  bitMask,
                           const  uint  doWriteTotalFalses,
                           global uint* totalFalses)
{
    // TODO cache in local memory?

    size_t i         = get_local_id(0);
    size_t group     = get_group_id(0);
    size_t groupSize = get_local_size(0);

    size_t groupOffset = group * groupSize * ELEMENTS_PER_WORK_ITEM_OTHERS;

    size_t itemOffset = ELEMENTS_PER_WORK_ITEM_OTHERS * i;

    prefixSums[ groupOffset + itemOffset     ] += sums[group];
    prefixSums[ groupOffset + itemOffset + 1 ] += sums[group];
//    prefixSums[ groupOffset + itemOffset + 2 ] += sums[group];
//    prefixSums[ groupOffset + itemOffset + 3 ] += sums[group];

    barrier(CLK_GLOBAL_MEM_FENCE);

    // If we are the first work item in the last work group

    if ( ( get_local_id(0) == 0 ) && ( group == (get_num_groups(0) - 1) ) )
    {
        if (doWriteTotalFalses)
        {
            // Add up possible false last element with last prefix sum

            uint lastIndex = count - 1;

            totalFalses[0] = !(elements[ lastIndex ] & bitMask) + prefixSums[ lastIndex ];
        }
    }

}


kernel void computeIndexAndScatter(global uint* elements,
                                   const  uint  count,
                                   global uint* prefixSums,
                                   global uint* totalFalses,
                                   const  uint  bitMask,
                                   global uint* elementsOut)
{

    size_t i         = get_local_id(0);
    size_t group     = get_group_id(0);
    size_t groupSize = get_local_size(0);

    size_t groupOffset = group * groupSize * ELEMENTS_PER_WORK_ITEM_OTHERS;

    size_t itemOffset = ELEMENTS_PER_WORK_ITEM_OTHERS * i;

    size_t i0 = groupOffset + itemOffset;
    size_t i1 = groupOffset + itemOffset + 1;
//    size_t i2 = groupOffset + itemOffset + 2;
//    size_t i3 = groupOffset + itemOffset + 3;

    size_t f0 = prefixSums[i0];
    size_t f1 = prefixSums[i1];
//    size_t f2 = prefixSums[i2];
//    size_t f3 = prefixSums[i3];

    uint totalFalsesCount = totalFalses[0];

    uint t0 = i0 - f0 + totalFalsesCount;
    uint t1 = i1 - f1 + totalFalsesCount;
//    uint t2 = i2 - f2 + totalFalsesCount;
//    uint t3 = i3 - f3 + totalFalsesCount;

    uint d0 = (elements[i0] & bitMask) ? t0 : f0;
    uint d1 = (elements[i1] & bitMask) ? t1 : f1;
//    uint d2 = (elements[i2] & bitMask) ? t2 : f2;
//    uint d3 = (elements[i3] & bitMask) ? t3 : f3;

    // Scatter elements

// TODO skip write if index does not change?

    uint lastIndex = count - 1;

    if (i0 <= lastIndex)
    {
        elementsOut[d0] = elements[i0];

        if (i1 <= lastIndex)
        {
            elementsOut[d1] = elements[i1];

 //           if (i2 <= lastIndex)
            {
//                elementsOut[d2] = elements[i2];

 //               if (i3 <= lastIndex)
                {
 //                   elementsOut[d3] = elements[i3];
                }
            }
        }
    }
}
