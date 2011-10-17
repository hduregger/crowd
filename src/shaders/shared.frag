uniform int             BUFFER_SIZE;

uniform float           colorScaleMin;
uniform float           colorScaleMax;

in      vec2            fragmentTexCoord;

out     vec4            fragmentData0;
out     vec4            fragmentData1;
out     vec4            fragmentData2;

const   float           PI  = 3.1415926535f;
const   float           PI2 = PI + PI;

const   float           POSITIVE_INFINITY = uintBitsToFloat(0x7f800000);

int getBufferIndex()
{
    // Convert form [0.0 1.0] to [0.0 BUFFER_SIZE]
    int x = int(fragmentTexCoord.x * BUFFER_SIZE);
    int y = int(fragmentTexCoord.y * BUFFER_SIZE);
    
    int iContributionX = x;
    int iContributionY = y * BUFFER_SIZE;

    int i = iContributionX + iContributionY;
    
    return i;
}


vec4 getArrowTexel(vec2 direction, sampler2D arrow, float scale, uint domainSize)
{
    vec4 texel;

    if ( (direction.x == 0.0f) && (direction.y == 0.0f) )
    {
        // Return black texel for zero direction

        texel = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
    
        // Compute coordinate inside the current arrow
        // Note: If all texels map directly to pixels then all pixels will be black.
        
        vec2 textureCoordinate = fract( fragmentTexCoord * float(domainSize) );
         
        if (scale <= 1.1f)
        {
            texel = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            // Rotate coordinate vector in local space
            
            textureCoordinate -= vec2(0.5f, 0.5f);
            
            mat2 rotation = mat2(direction, vec2(direction.y, -direction.x));
            
            textureCoordinate = rotation * textureCoordinate;
            
            textureCoordinate += vec2(0.5f, 0.5f);
            
            // Lookup arrow texel
            
            texel = texture(arrow, textureCoordinate);
        }
    }

    return texel;
}


vec4 mapToLegend(float value, sampler2D legend)
{
    float min = colorScaleMin;
    float max = colorScaleMax;
    
    float diff = max - min;
    
    value = value - min;
    
    float percent = value / diff;
    percent = clamp(percent, 0.0f, 1.0f);
    
    vec4 color = texture(legend, vec2(0.0f, percent));
    
    return color;    
}


vec4 mapToLegend(vec2 direction)
{
    direction.x = (direction.x + 1.0f) * 0.5f;
    direction.y = (direction.y + 1.0f) * 0.5f;
    
    return vec4(direction, 0.0f, 1.0f);
}

/**
 * Expects normalized direction.
 */

vec4 mapToLegend(vec2 direction, sampler2D legend)
{
    vec4 color;
    
    if ( (direction.x == 0.0f) && (direction.y == 0.0f) )
    {
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        float angle = atan(direction.y, direction.x);
        
        if (direction.y < 0.0f)
        {
            // Angle is negative, subtract it from 2 PI
            
            angle += PI2;
        }
        
        float percent = angle / PI2;
        
        color = texture(legend, vec2(0.0f, percent));
    }
    
    return color;
}


void debugRender(float f)
{
    if (isnan(f))
    {
        fragmentData0 = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }
    else if (isinf(f))
    {
        fragmentData0 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}


void debugRenderVector(vec2 v)
{
    if (isnan(v.x) || isnan(v.y))
    {
        fragmentData0 = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }
    else if (isinf(v.x) || isinf(v.y))
    {
        fragmentData0 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

