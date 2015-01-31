#version 140

out vec4 outputColor;

uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;

in vec3 fragPosition;
in vec3 fragNormal;

void main()
{

    vec3 surfaceToLight = uLightPosition - fragPosition;

    float brightness = dot(fragNormal, surfaceToLight) / (length(surfaceToLight) * length(fragNormal));
    brightness = clamp(brightness, 0, 1);


    outputColor = vec4(brightness * uLightColor * uColor.rgb, uColor.a);
}
