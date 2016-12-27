#version 140

in vec3 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

uniform mat4 uModelViewProjMat;
uniform vec2 uOffset;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

void main()
{
    float scale = 1.0f;
    
	fragPosition = aPosition;
	fragNormal = aNormal;
    fragTexCoord = aTexCoord;

    gl_Position = uModelViewProjMat * vec4(aPosition.xy * scale + uOffset, 0.0, 1.0);
}
