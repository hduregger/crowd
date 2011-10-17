// For display of the average velocity texture

uniform samplerBuffer   textureSampler;
uniform sampler2D       legend;
uniform sampler2D       arrow;

uniform float           scale;
uniform uint            domainSize;

void main()
{
	vec4 c = texelFetch(textureSampler, getBufferIndex());

	vec2 v = c.zw;

	// NOTE: normalization hides infinity

	v = normalize(v);

    fragmentData0 = mapToLegend(v, legend) * getArrowTexel(v, arrow, scale, domainSize);

    // Use original value because of hiding

    debugRenderVector(c.zw);
}
