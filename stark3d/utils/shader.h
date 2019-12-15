#ifndef UTIL_SHADER_H
#define UTIL_SHADER_H

#include "global.h"
#include "utils/linmath.h"

#include <string>

SK_BEGIN_NAMESPACE

class ShaderUniforms
{
public:
    ShaderUniforms();
public:
    mat4x4 mv;
    mat4x4 mvp;
    vec4 color;
    vec3 lightPosition;
    vec3 lightColor;
    uint32 activeTexture;
    uint32 activeTexture2;
    mat4x4 filter;
    float viewportWidth;
    float viewportHeight;

private:
    int32 mvLoc;
    int32 mvpLoc;
    int32 colorLoc;
    int32 lightPositionLoc;
    int32 lightColorLoc;
    int32 colorMapLoc;
    int32 colorMapLoc2;
    int32 filterLoc;
    int32 viewportWidthLoc;
    int32 viewportHeightLoc;

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