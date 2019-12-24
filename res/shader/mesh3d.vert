#version 140

in vec3 aPosition;
in vec3 aNormal;
uniform mat4 uMVP;

out vec3 fragPosition;
out vec3 fragNormal;

void main()
{
    gl_Position = uMVP * vec4(aPosition, 1.0);
    fragPosition = aPosition;
    fragNormal = aNormal;
}
