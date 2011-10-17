// For display of the cost texture

uniform samplerBuffer   textureSampler;
uniform samplerBuffer   textureSampler1;
uniform float           alpha;
uniform int             index;


const int    GROUP_STATE_SLEEP          = 0;
const int    GROUP_STATE_IS_CONVERGED   = 1;
const int    GROUP_STATE_UPDATE         = 2;


void main()
{
    int i = getBufferIndex();
    
    float f;
    
    switch (index)
    {
        case 0:
        {
            f = texelFetch(textureSampler, i).x;
            break;
        }
        
        default:
        {
            f = texelFetch(textureSampler1, i).x;
            break;
        }    
    }

    int c = floatBitsToInt(f);

    switch (c)
    {
        case GROUP_STATE_SLEEP:
        {
            // Red
            fragmentData0 = vec4(1.0f, 0.0f, 0.0f, 1.0f);
            break;
        }
        
        case GROUP_STATE_UPDATE:
        {
            // Green
            fragmentData0 = vec4(0.0f, 1.0f, 0.0f, 1.0f);
            break;
        }
        
        case GROUP_STATE_IS_CONVERGED:
        {
            // Blue
            fragmentData0 = vec4(0.0f, 0.0f, 1.0f, 1.0f);
            break;
        }
                
        default:
        {
            // Purple
            fragmentData0 = vec4(1.0f, 0.0f, 1.0f, 1.0f);
            break;
        }
    }
    
    debugRender(c);
    
    fragmentData0.a = alpha;
}
