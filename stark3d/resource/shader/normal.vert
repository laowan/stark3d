#version 140

in vec3 position;
in vec3 normal;

uniform mat4 uModelViewMat;
uniform mat4 uModelViewProjMat;

out vec3 fragPosition;
out vec3 fragNormal;

void main()
{
    fragPosition = position;
    fragNormal = normal;

    gl_Position = uModelViewProjMat * vec4(position, 1.0);
}
