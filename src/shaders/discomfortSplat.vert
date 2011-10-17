struct Camera
{
    mat4   projection;
    vec3   position;
};

uniform         Camera  camera;
uniform         float   radius;
uniform         vec2    position;

// Note: due to a bug in the Catalyst drivers attrib name must be alphabetically
//       before gl_ names or things like gl_instanceID will mess up (likely fixed now)
in              vec4    _vertex;

flat out   mat4    projection;
flat out   float   radiusGeom;


void main()
{
    projection  = camera.projection;

    vec4 v = _vertex;

    radiusGeom = radius;

    v.xy += position;

    v.z = 0.0f;
    v.w = 1.0f;

    gl_Position = (v - vec4(camera.position, 0.0f));
}


