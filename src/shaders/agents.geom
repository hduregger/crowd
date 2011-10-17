layout(points) in;
layout(triangle_strip, max_vertices = 4) out;


flat in     mat4    projection[];
flat in     float   radiusGeom[];

flat in     mat2    rotation[];

smooth out  vec2    texCoordFrag;

flat in     uint    group[];
flat out    uint    groupFrag;


void emitVertex(float dx, float dy, vec2 texCoord)
{
    vec4 p = gl_in[0].gl_Position + vec4(dx, dy, 0.0f, 0.0f);

    gl_Position = projection[0] * p;

    texCoordFrag = rotation[0] * (texCoord - vec2(0.5f, 0.5f)) + vec2(0.5f, 0.5f);

    groupFrag = group[0];
    
    EmitVertex();
}


void main()
{
    float radiusPos = radiusGeom[0];
    float radiusNeg = -radiusPos;

    emitVertex(radiusNeg, radiusNeg, vec2(0.0f, 0.0f));
    emitVertex(radiusNeg, radiusPos, vec2(0.0f, 1.0f));
    emitVertex(radiusPos, radiusNeg, vec2(1.0f, 0.0f));
    emitVertex(radiusPos, radiusPos, vec2(1.0f, 1.0f));

    gl_PrimitiveID = gl_PrimitiveIDIn;

    EndPrimitive();
}
