#version 140

out vec4 outputColor;

uniform sampler2D uColorMap;
uniform vec4 uColor;

in vec2 fragTexCoord;

void main()
{
	vec4 color = texture(uColorMap, fragTexCoord);
	outputColor = color;
}
