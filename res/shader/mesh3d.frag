#version 140

out vec4 outputColor;

in vec3 fragPosition;
in vec3 fragNormal;

void main()
{
    vec3 lightPosition = vec3(0.0, 0.0, 2.0);
    vec3 lightColor = vec3(1.0);
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 result = diff * lightColor;
    norm = 0.5 * (norm + vec3(1.0));
    outputColor = vec4(norm, 1.0);
}
