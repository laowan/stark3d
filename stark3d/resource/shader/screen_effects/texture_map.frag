#version 140

out vec4 outputColor;

uniform sampler2D uColorMap;
uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform mat4 uFilterMat;
uniform float uViewportWidth;
uniform float uViewportHeight;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

void main()
{
	vec4 samples[4];
	samples[0] = vec4(-1.0, 0.0, 0.0, 0.25);
	samples[1] = vec4( 1.0, 0.0, 0.0, 0.25);
	samples[2] = vec4( 0.0, 1.0, 0.0, 0.25);
	samples[3] = vec4( 0.0,-1.0, 0.0, 0.25);
	
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++)
	{
		vec2 offset;
		offset.x = samples[i].x * (1.0 / uViewportWidth);
		offset.y = samples[i].y * (1.0 / uViewportHeight);
		color += samples[i].w * texture(uColorMap, fragTexCoord + offset);
	}
	
    outputColor = color;
}
