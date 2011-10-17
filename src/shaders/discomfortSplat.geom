layout(points) in;
layout(triangle_strip, max_vertices = 4) out;


flat in     mat4    projection[];
flat in     float   radiusGeom[];

smooth out  vec2    texCoordFrag;


void emitVertex(float dx, float dy, vec2 texCoord)
{
    vec4 p = gl_in[0].gl_Position + vec4(dx, dy, 0.0f, 0.0f);

    gl_Position = projection[0] * p;

    texCoordFrag = texCoord;

    EmitVertex();
}


void main()
{
    float radiusPos = radiusGeom[0];
    float radiusNeg = -radiusPos;
    
    // Emit discomfort splat

    emitVertex(radiusNeg, radiusNeg, vec2(0.0f, 0.0f));
    emitVertex(radiusNeg, radiusPos, vec2(0.0f, 1.0f));
    emitVertex(radiusPos, radiusNeg, vec2(1.0f, 0.0f));
    emitVertex(radiusPos, radiusPos, vec2(1.0f, 1.0f));

    EndPrimitive();
}
