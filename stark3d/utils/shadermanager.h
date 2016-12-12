#ifndef UTILS_SHADERMANAGER_H
#define UTILS_SHADERMANAGER_H

#include "global.h"
#include "shader.h"

SK_BEGIN_NAMESPACE

class STARK_API ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void use(std::string name);
    Shader* getShader(std::string name);
    Shader* currentShader();

private:
    SK_DECLARE_IMPL(ShaderManager);
};

SK_END_NAMESPACE

#endif