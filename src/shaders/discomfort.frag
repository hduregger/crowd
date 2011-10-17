// For display of the discomfort texture

uniform sampler2D   textureSampler;
uniform sampler2D   legend;


void main()
{
    float c = texture(textureSampler, fragmentTexCoord).y;

	fragmentData0 = mapToLegend(c, legend);


	debugRender(c);
} 
