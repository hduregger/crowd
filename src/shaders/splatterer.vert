struct Camera
{
    mat4   projection;
    vec3   position;
};

uniform samplerBuffer   positions;
uniform samplerBuffer   directions;
uniform samplerBuffer   speeds;
uniform samplerBuffer   ids;
uniform samplerBuffer   radii;

uniform         Camera  camera;


// Note: due to a bug in the Catalyst drivers attrib name must be alphabetically
//       before gl_ names or things like gl_instanceID will mess up (likely fixed now)
in              vec4    _vertex;


flat out   mat4    projection;
flat out   float   radiusGeom2;

flat out   vec2    directionGeom;
flat out   vec2    velocity;
flat out   uint    group; 


void main()
{
            
    projection  = camera.projection;

    vec4 v = _vertex;

    // Read position and velocity from texture

    vec2  position  = texelFetch(positions,  gl_InstanceID).xy;
    vec2  direction = texelFetch(directions, gl_InstanceID).xy;
    
    directionGeom = direction;
    
    float speed     = texelFetch(speeds,     gl_InstanceID).x;
    
    group = floatBitsToUint(texelFetch(ids, gl_InstanceID).x);
    
    float radius = texelFetch(radii,  gl_InstanceID).x;
    radiusGeom2 = radius + radius;

    velocity = direction * speed;

    // Move agent to its position

    v.xy += position;

    v.z = 0.0f;
    v.w = 1.0f;

    gl_Position = (v - vec4(camera.position, 0.0f));
}


