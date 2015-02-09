#ifndef UTILS_SHADERMANAGER_H
#define UTILS_SHADERMANAGER_H

#include "global.h"
#include "shader.h"
#include <map>

SK_BEGIN_NAMESPACE

class ShaderManager
{
public:
    enum ShaderType
    {
        SD_NORMAL
    };

public:
    ShaderManager();
    ~ShaderManager();

    void use(ShaderType type);
    Shader* getShader(ShaderType type) { return _shaderMap[type];  }
    Shader* currentShader() { return _curShader; }

private:
    std::map<ShaderType, Shader*> _shaderMap;
    Shader* _curShader;
};

SK_END_NAMESPACE

#endif