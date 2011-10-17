// For display of the map

uniform sampler2D   textureSampler;
uniform float       alpha;


void main()
{
    fragmentData0.rgb = texture(textureSampler, fragmentTexCoord).rgb;
    fragmentData0.a   = alpha;
}
