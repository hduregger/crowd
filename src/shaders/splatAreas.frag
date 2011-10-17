// For display of the agents texture

uniform sampler2D   textureSampler;

void main()
{
    fragmentData0 = texture(textureSampler, fragmentTexCoord);
} 
