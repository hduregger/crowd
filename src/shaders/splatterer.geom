layout(points) in;
layout(triangle_strip, max_vertices = 8) out;


flat in     mat4    projection[];
flat in     float   radiusGeom2[];

smooth out  vec2    texCoordFrag;

flat in     vec2    velocity[];
flat out    vec2    velocityFrag;

flat in     vec2    directionGeom[];

flat in     uint    group[];
flat out    uint    groupFrag;

//flat out    bool    isDiscomfortFrag;


void emitVertex(float dx, float dy, vec2 texCoord, vec2 vel)//, bool isDiscomfort)
{
    vec4 p = gl_in[0].gl_Position + vec4(dx, dy, 0.0f, 0.0f);

    gl_Position = projection[0] * p;

    texCoordFrag = texCoord;

    groupFrag = group[0];

    velocityFrag = vel;
    
//    isDiscomfortFrag = isDiscomfort;

    EmitVertex();
}


void main()
{
    float radiusPos2 = radiusGeom2[0];
    float radiusNeg2 = -radiusPos2;
    
    vec2 vel = velocity[0];
    
    // Emit density and velocity primitive

    emitVertex(radiusNeg2, radiusNeg2, vec2(0.0f, 0.0f), vel);//, false);
    emitVertex(radiusNeg2, radiusPos2, vec2(0.0f, 1.0f), vel);//, false);
    emitVertex(radiusPos2, radiusNeg2, vec2(1.0f, 0.0f), vel);//, false);
    emitVertex(radiusPos2, radiusPos2, vec2(1.0f, 1.0f), vel);//, false);

    EndPrimitive();

/*
    // Emit discomfort primitive
    
    vec2 offset = radiusPos2 * directionGeom[0] * 2.0f;
    
    float radiusPos2OffsetX = radiusPos2 + offset.x;
    float radiusPos2OffsetY = radiusPos2 + offset.y;
    float radiusNeg2OffsetX = radiusNeg2 + offset.x;
    float radiusNeg2OffsetY = radiusNeg2 + offset.y;
    
    
    emitVertex(radiusNeg2OffsetX, radiusNeg2OffsetY, vec2(0.0f, 0.0f), vel, true);
    emitVertex(radiusNeg2OffsetX, radiusPos2OffsetY, vec2(0.0f, 1.0f), vel, true);
    emitVertex(radiusPos2OffsetX, radiusNeg2OffsetY, vec2(1.0f, 0.0f), vel, true);
    emitVertex(radiusPos2OffsetX, radiusPos2OffsetY, vec2(1.0f, 1.0f), vel, true);

    EndPrimitive();
*/
}
