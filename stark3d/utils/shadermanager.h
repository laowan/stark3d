#ifndef UTILS_SHADERMANAGER_H
#define UTILS_SHADERMANAGER_H

#include "shader.h"
#include <map>

namespace Util {

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

}

#endif