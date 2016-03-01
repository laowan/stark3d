#version 140

out vec4 outputColor;

uniform sampler2D uColorMap;
uniform sampler2D uColorMap2;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

void main()
{
	vec4 color1 = texture(uColorMap, fragTexCoord);
	vec4 color2 = texture(uColorMap2, fragTexCoord);
	
    outputColor = mix(color1, color2, 0.3);
}
