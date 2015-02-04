#ifndef UTIL_SHADER_H
#define UTIL_SHADER_H

#include <string>

namespace Util {

class ShaderUniforms
{
public:
    unsigned int mvpUniform;
    unsigned int color;
    unsigned int lightPosition;
    unsigned int lightColor;
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

private:
    void bind();

private:
    int _program;
    ShaderUniforms _uniforms;
};

}

#endif