#ifndef UTIL_SHADER_H
#define UTIL_SHADER_H

#include "global.h"
#include <string>
#include "glm/glm.hpp"

SK_BEGIN_NAMESPACE

class ShaderUniforms
{
public:
    ShaderUniforms();
public:
    glm::mat4 mv;
    glm::mat4 mvp;
    glm::vec4 color;
    glm::vec3 lightPosition;
    glm::vec3 lightColor;
    uint32 activeTexture;
    uint32 activeTexture2;
    glm::mat4 filter;
    float viewportWidth;
    float viewportHeight;

private:
    uint32 mvLoc;
    uint32 mvpLoc;
    uint32 colorLoc;
    uint32 lightPositionLoc;
    uint32 lightColorLoc;
    uint32 colorMapLoc;
    uint32 colorMapLoc2;
    uint32 filterLoc;
    uint32 viewportWidthLoc;
    uint32 viewportHeightLoc;

friend class Shader;
};

class STARK_API Shader
{
public:
    Shader(std::string filename);
    ~Shader();

    void init(std::string filename);
    void use();
    int program();
    ShaderUniforms& uniforms();
    void commitUniforms();

private:
    void bind();

private:
    SK_DECLARE_IMPL(Shader);
};

SK_END_NAMESPACE

#endif