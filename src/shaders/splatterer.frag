uniform     sampler2D   agent;

smooth in   vec2        texCoordFrag;

flat in     vec2        velocityFrag;
flat in     uint        groupFrag;

//flat in     bool        isDiscomfortFrag;


/**
 * Write agent data to buffer. The data of individual agents is summed up by blending.
 *
 * fragmentData0.x - density
 * fragmentData0.y - discomfort
 * fragmentData0.z - weighted velocity x
 * fragmentData0.w - weighted velocity y
 *
 * fragmentData1   - appearance color
 */

void main()
{
    vec4 c = texture(agent, texCoordFrag);

    //
    // Write agent density
    //

    float density = c.r * c.a;
    
    
//    if (isDiscomfortFrag)
//    {
//        fragmentData0 = vec4(0.0f, density, 0.0f, 0.0f);
//    }
//    else
//    {
        vec2 weightedVelocity = velocityFrag * density;
        
        fragmentData0 = vec4(density, 0.0f, weightedVelocity.x, weightedVelocity.y);
//    }
    
    //
    // Write agent appearance
    //

    switch (groupFrag)
    {
        case 0:
        {
            // yellow
            fragmentData1 = vec4(0.9f, 0.9f, 0.0f, 1.0f) * c.a;
            break;
        }
        
        case 1:
        {
            // cyan
            fragmentData1 = vec4(0.0f, 0.9f, 0.9f, 1.0f) * c.a;
            break;
        }
        
        case 2:
        {
            // purple
            fragmentData1 = vec4(0.9f, 0.0f, 0.9f, 1.0f) * c.a;
            break;
        }
        
        case 3:
        {
            // white
            fragmentData1 = vec4(0.9f, 0.9f, 0.9f, 1.0f) * c.a;
            break;
        }
    }
}
