#version 140

in vec3 aPosition;
in vec3 aNormal;
in vec2 aTextureCoord;
uniform mat4 uMVP;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTextureCoord;

void main()
{
    gl_Position = uMVP * vec4(aPosition, 1.0);
    fragPosition = aPosition;
    fragNormal = aNormal;
    fragTextureCoord = aTextureCoord;
    
}
