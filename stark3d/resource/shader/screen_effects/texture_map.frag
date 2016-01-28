#version 140

out vec4 outputColor;

uniform sampler2D uColorMap;
uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

void main()
{
    outputColor = texture(uColorMap, fragTexCoord);
}
