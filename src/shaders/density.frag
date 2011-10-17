// For display of the density texture

uniform sampler2D   textureSampler;
uniform sampler2D   legend;


void main()
{
    float c = texture(textureSampler, fragmentTexCoord).x;

	fragmentData0 = mapToLegend(c, legend);


	debugRender(c);
} 
