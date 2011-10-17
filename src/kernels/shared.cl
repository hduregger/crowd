constant float4     ZEROS       = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
constant float4     ONES        = (float4)(1.0f, 1.0f, 1.0f, 1.0f);

constant float4     INFINITIES  = (float4)(INFINITY, INFINITY, INFINITY, INFINITY);

constant uint       ID_GROUP_MASK = 0x3;


int2 positionFromIndex(int i, int width)
{
    int2 p;

    p.x = i % width;
    p.y = i / width;

    return p;
}


int indexFromPosition(int2 p, int width)
{
    int i;

    i = p.x + p.y * width;

    return i;
}

/**
 * Returns true if the position is inside the buffer with given side length size.
 */

bool isInside(int2 p, int size)
{
    return (p.x >= 0) && (p.x < size) && (p.y >= 0) && (p.y < size);
}


/**
 * Returns true if the position is inside the image with given side length size.
 * P is treated as unnormalized coordinates into the image. Which means, for an
 * image with size = 128, p = (float2)(128.0f, 128.0f) is inside the image.
 */

bool isInsideFloat(float2 p, int size)
{
    return (p.x >= 0) && (p.x <= size) && (p.y >= 0) && (p.y <= size);
}


float4 getValueOrInfinity(int2 p, int size, global float4* array)
{
    float4 v;
    
    int4 isInsideArea = isInside(p, size);
    
    float4 arrayValue = array[ clamp(indexFromPosition(p, size), 0, size * size - 1) ];
    
    v = select(INFINITIES, arrayValue, isInsideArea);

    return v;
}


float4 getValueOrZero(int2 p, int size, global float4* array)
{
    float4 v;
    
    int4 isInsideArea = isInside(p, size);
    
    float4 arrayValue = array[ clamp(indexFromPosition(p, size), 0,  size * size - 1) ];
    
    v = select(ZEROS, arrayValue, isInsideArea);

    return v;
}


float4 getValueWithBilinearFilteringOrZero(float2 position, int size, read_only image2d_t image)
{
    float4 v;
    
    int4 isInsideArea = isInsideFloat(position, size);
    
    float4 imageValue = read_imagef(image, CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_LINEAR, position);
    
    v = select(ZEROS, imageValue, isInsideArea);

    return v;
}


int getIntOrZeroRestrict(int2 p, size_t size, global int const* restrict array)
{
    int isInsideArea = isInside(p, size);
    
    if (isInsideArea)
    {
        return array[indexFromPosition(p, size)];
    }
    else
    {
        return 0;
    }
}


float4 getNESWNeighborsXComponentOrInfinity(int2 position, int bufferSideLength, global float4* buffer)
{
    int2 positionNorth = position;
    int2 positionEast  = position;
    int2 positionSouth = position;
    int2 positionWest  = position;

    positionNorth.y += 1;
    positionEast.x  += 1;
    positionSouth.y -= 1;
    positionWest.x  -= 1;
    
    float4 neighbors;

    neighbors.x  = getValueOrInfinity(positionNorth, bufferSideLength, buffer).x;
    neighbors.y  = getValueOrInfinity(positionEast,  bufferSideLength, buffer).x;
    neighbors.z  = getValueOrInfinity(positionSouth, bufferSideLength, buffer).x;
    neighbors.w  = getValueOrInfinity(positionWest,  bufferSideLength, buffer).x;
    
    return neighbors;
}


float4 getNESWNeighborsYComponentOrInfinity(int2 position, int bufferSideLength, global float4* buffer)
{
    int2 positionNorth = position;
    int2 positionEast  = position;
    int2 positionSouth = position;
    int2 positionWest  = position;

    positionNorth.y += 1;
    positionEast.x  += 1;
    positionSouth.y -= 1;
    positionWest.x  -= 1;
    
    float4 neighbors;

    neighbors.x  = getValueOrInfinity(positionNorth, bufferSideLength, buffer).y;
    neighbors.y  = getValueOrInfinity(positionEast,  bufferSideLength, buffer).y;
    neighbors.z  = getValueOrInfinity(positionSouth, bufferSideLength, buffer).y;
    neighbors.w  = getValueOrInfinity(positionWest,  bufferSideLength, buffer).y;
    
    return neighbors;
}


size_t getIGlobalGroupBase(const uint workGroupSideLength)
{
    return get_group_id(0) * workGroupSideLength * workGroupSideLength;
}


size_t getLocalX(const uint workGroupSideLength)
{
    return get_local_id(0) % workGroupSideLength;
}


size_t getLocalY(const uint workGroupSideLength)
{
    return get_local_id(0) / workGroupSideLength;
}


size_t getGlobalBaseX(const uint workGroupSideLength, const uint bufferSideLength)
{
    return (get_group_id(0) * workGroupSideLength) % bufferSideLength;
}


size_t getGlobalBaseY(const uint workGroupSideLength, const uint bufferSideLength)
{
    return get_group_id(0) * workGroupSideLength / bufferSideLength * workGroupSideLength;
}

/**
 * Reduction for power of two buffers and the logical AND operation
 * based on
 * http://developer.amd.com/documentation/articles/Pages/OpenCL-Optimization-Case-Study-Simple-Reductions_4.aspx
 */

int reduceAnd(local int* booleans, size_t localId, size_t localSize)
{
    for (int offset = localSize / 2;  offset > 0; offset >>= 1)
    {
        if (localId < offset)
        {
            int isTrueA = booleans[localId         ];
            int isTrueB = booleans[localId + offset];
            
            booleans[localId] = isTrueA && isTrueB;
        }
        
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    return booleans[0];
}

/**
 * Reduction for power of two buffers and the logical OR operation
 * based on
 * http://developer.amd.com/documentation/articles/Pages/OpenCL-Optimization-Case-Study-Simple-Reductions_4.aspx
 */

int reduceOr(local int* booleans, size_t localId, size_t localSize)
{
    for (int offset = localSize / 2;  offset > 0; offset >>= 1)
    {
        if (localId < offset)
        {
            int isTrueA = booleans[localId         ];
            int isTrueB = booleans[localId + offset];
            
            booleans[localId] = isTrueA || isTrueB;
        }
        
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    
    return booleans[0];
}


float getPotentialInfinity(uint                group,
                           int2                gridPosition,
                           const uint          BUFFER_SIDE_LENGTH,
                           global float4*      potentials)
{
    float potential;
    
    switch (group)
    {
        case 0:
        {
            potential = getValueOrInfinity(gridPosition, BUFFER_SIDE_LENGTH, potentials).x;
            break;
        }
        
        case 1:
        {
            potential = getValueOrInfinity(gridPosition, BUFFER_SIDE_LENGTH, potentials).y;
            break;
        }
        
        case 2:
        {
            potential = getValueOrInfinity(gridPosition, BUFFER_SIDE_LENGTH, potentials).z;
            break;
        }
        
        case 3:
        {
            potential = getValueOrInfinity(gridPosition, BUFFER_SIDE_LENGTH, potentials).w;
            break;
        }
    }
    
    return potential;
}