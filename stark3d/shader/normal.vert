#version 140

in vec4 position;
in vec4 color;

smooth out vec4 theColor;

uniform vec2 offset;
uniform mat4 uModelViewMat;
uniform mat4 uModelViewProjMat;

void main()
{
    gl_Position = uModelViewProjMat * position;
    theColor = color;
}
