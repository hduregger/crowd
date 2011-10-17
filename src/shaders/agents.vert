struct Camera
{
    mat4   projection;
    vec3   position;
};

uniform samplerBuffer   positions;
uniform samplerBuffer   directions;
uniform samplerBuffer   ids;
uniform samplerBuffer   radii;

uniform         Camera  camera;


// Note: due to a bug in the Catalyst drivers attrib name must be alphabetically
//       before gl_ names or things like gl_instanceID will mess up (likely fixed now)
in              vec4    _vertex;

flat out   mat4    projection;
flat out   float   radiusGeom;

flat out   mat2    rotation;

flat out   uint    group; 


void main()
{

    projection  = camera.projection;

    vec4 v = _vertex;

    // Read position and velocity from texture

    vec2  position  = texelFetch(positions,  gl_InstanceID).xy;
    vec2  direction = texelFetch(directions, gl_InstanceID).xy;
    
    group = floatBitsToUint(texelFetch(ids, gl_InstanceID).x);

    radiusGeom = texelFetch(radii,  gl_InstanceID).x;
    
    // Move agent to its position

    v.xy += position;

    v.z = 0.0f;
    v.w = 1.0f;

  
    rotation = mat2(direction, vec2(direction.y, -direction.x));

    gl_Position = (v - vec4(camera.position, 0.0f));
}


