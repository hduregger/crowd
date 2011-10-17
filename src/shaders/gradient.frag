// For display of the gradient texture

uniform sampler2D       textureSampler;
uniform sampler2D       textureSampler23;
uniform sampler2D       legend;
uniform sampler2D       arrow;

uniform uint            component;
uniform uint            pass;
uniform uint            domainSize;

uniform float           scale;

uniform float           alpha;


void main()
{
	vec2 c;
	
	// Retrieve gradient
	
    switch (component)
    {
        case 0:
        {
            c = texture(textureSampler, fragmentTexCoord).xy;
            break;
        }

        case 1:
        {
            c = texture(textureSampler, fragmentTexCoord).zw;
            break;
        }

        case 2:
        {
            c = texture(textureSampler23, fragmentTexCoord).xy;
            break;
        }

        case 3:
        {
            c = texture(textureSampler23, fragmentTexCoord).zw;
            break;
        }

        default:
        {
            float nan = 0.0f / 0.0f;

            c = vec2(nan, nan);
            
            break;
        }

    }
	
	vec2 gradient = c;

	// NOTE: normalization hides infinity

	gradient = normalize(gradient);

	switch (pass)
	{
	    case 0:
	    {
	        fragmentData0 = mapToLegend(gradient, legend);
	        
	        // Use original value because of hiding

	        debugRenderVector(c);

	        break;
	    }
	    
	    default:
        {
            fragmentData0 = getArrowTexel(gradient, arrow, scale, domainSize);
            fragmentData0.a = alpha;
            break;
        }
	}
} 
