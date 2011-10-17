uniform     sampler2D   agent;

smooth in   vec2        texCoordFrag;

uniform     float       factor;

/**
 * Write discomfort splat to buffer.
 *
 * fragmentData0.x - density
 * fragmentData0.y - discomfort
 * fragmentData0.z - weighted velocity x
 * fragmentData0.w - weighted velocity y
 *
 * fragmentData1   - appearance color
 */

void main()
{
    // We use the agent circle splat texture for splatting discomfort at pointer location
    
    vec4 c = texture(agent, texCoordFrag);

    //
    // Write discomfort brush
    //

    fragmentData0 = vec4(0.0f, c.r * c.a * factor, 0.0f, 0.0f);

    
    fragmentData1 = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
