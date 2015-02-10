#ifndef UTIL_SHADER_H
#define UTIL_SHADER_H

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class ShaderUniforms
{
public:
    glm::mat4 mvp;
    glm::vec4 color;
    glm::vec3 lightPosition;
    glm::vec3 lightColor;

private:
    unsigned int mvpLoc;
    unsigned int colorLoc;
    unsigned int lightPositionLoc;
    unsigned int lightColorLoc;

friend class Shader;
};

class Shader
{
public:
    Shader(std::string filename);
    ~Shader();

    void init(std::string filename);
    void use();
    int program() { return _program; }
    ShaderUniforms& uniforms() { return _uniforms; }
    void commitUniforms();

private:
    void bind();

private:
    int _program;
    ShaderUniforms _uniforms;
};

SK_END_NAMESPACE

#endif