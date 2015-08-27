#version 140

in vec3 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

uniform mat4 uModelViewMat;
uniform mat4 uModelViewProjMat;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

void main()
{
	vec4 tmp = uModelViewMat * vec4(aPosition, 1.0);
	fragPosition = tmp.xyz;

	fragNormal = mat3x3(uModelViewMat) * aNormal;
	
    fragTexCoord = aTexCoord;

    gl_Position = uModelViewProjMat * vec4(aPosition, 1.0);
}
