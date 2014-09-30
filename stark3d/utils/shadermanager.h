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
    static ShaderManager* instance()
    {
        static ShaderManager manager;
        return &manager;
    }

public:
    void use(ShaderType type);
    Shader* getShader(ShaderType type) { return _shaderMap[type];  }

private:
    std::map<ShaderType, Shader*> _shaderMap;
};

}

#endif