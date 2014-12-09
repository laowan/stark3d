#version 140

in vec3 position;

uniform mat4 uModelViewMat;
uniform mat4 uModelViewProjMat;

void main()
{
    gl_Position = uModelViewProjMat * vec4(position, 1.0);
}
