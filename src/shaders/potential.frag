
uniform samplerBuffer   textureSampler;
uniform sampler2D       legend;
uniform uint            component;

void main()
{
	int i = getBufferIndex();

	float c = abs( texelFetch(textureSampler, i)[component] );

    fragmentData0 = mapToLegend(c, legend);

    debugRender(c);

} 
