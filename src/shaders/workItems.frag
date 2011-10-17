// For display of the work items areas

uniform samplerBuffer   textureSampler;
uniform float           alpha;


void main()
{
	int i = getBufferIndex();

	vec4 c = vec4(texelFetch(textureSampler, i).x);

    fragmentData0 = c;

    debugRender(c.x);

    fragmentData0.a = alpha;
} 
