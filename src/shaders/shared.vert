struct Camera
{
    mat4   projection;
    vec3   position;
};

uniform Camera camera;

// Note: due to a bug in the Catalyst drivers attrib name must be alphabetically
//       before gl_ names or things like gl_instanceID will mess up (likely fixed now)
in 		vec4 _vertex;
in 		vec2 _texCoord;

out		vec2 fragmentTexCoord;


void main()
{
	fragmentTexCoord = _texCoord;

	gl_Position      = camera.projection * (_vertex - vec4(camera.position, 0.0f));
}


