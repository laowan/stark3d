#version 140

out vec4 outputColor;

uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;

in vec3 fragPosition;
in vec3 fragNormal;

void main()
{

    vec3 normal = normalize(fragNormal);
    vec3 surfaceToLight = normalize(uLightPosition - fragPosition);

    //float brightness = dot(fragNormal, surfaceToLight) / (length(surfaceToLight) * length(fragNormal));
    //brightness = clamp(brightness, 0, 1);
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * uLightColor * uColor.rgb;

    vec3 ambient = 0.5 * uLightColor * uColor.rgb;

    outputColor = vec4(ambient + diffuse, uColor.a);
}
