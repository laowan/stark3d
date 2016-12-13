#version 140

in vec3 aPosition;
in vec2 aTexCoord;

uniform mat4 uModelViewProjMat;

out vec2 fragTexCoord;

void main()
{
    fragTexCoord = aTexCoord;

    gl_Position = uModelViewProjMat * vec4(aPosition, 1.0);
}
