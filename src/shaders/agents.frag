smooth in   vec2        texCoordFrag;

uniform     sampler2D   agent0;
uniform     sampler2D   agent1;
uniform     sampler2D   agent2;
uniform     sampler2D   agent3;

flat in     uint        groupFrag;


void main()
{
    // Handle rotated texture coordinates

    if ((texCoordFrag.x < 0.0f) || (texCoordFrag.x > 1.0f) ||
        (texCoordFrag.y < 0.0f) || (texCoordFrag.y > 1.0f)    )
    {
        discard;
    }
    else
    {
        //
        // Write agent appearance
        //
        
        switch (groupFrag)
        {
            case 0:
            {
                fragmentData0 = texture(agent0, texCoordFrag);
                break;
            }
            
            case 1:
            {
                fragmentData0 = texture(agent1, texCoordFrag);
                break;
            }
            
            case 2:
            {
                fragmentData0 = texture(agent2, texCoordFrag);
                break;
            }
            
            case 3:
            {
                fragmentData0 = texture(agent3, texCoordFrag);
                break;
            }
        }
    }
}
