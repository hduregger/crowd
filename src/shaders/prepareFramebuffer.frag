
uniform samplerBuffer   textureSampler;

const float WALL_THRESHOLD_DISCOMFORT =    0.99f;

void main()
{
	int i = getBufferIndex();
	
	float discomfort = texelFetch(textureSampler, i).x;
	
	if (discomfort >= WALL_THRESHOLD_DISCOMFORT)
	{
	    discomfort = POSITIVE_INFINITY;
	}

	fragmentData0 = vec4(0.0f, discomfort, 0.0f, 0.0f);
	fragmentData1 = vec4(0.0f, 0.0f,       0.0f, 0.0f);
} 
