#ifndef UTILS_SHADERMANAGER_H
#define UTILS_SHADERMANAGER_H

#include "global.h"
#include "shader.h"
#include <map>

SK_BEGIN_NAMESPACE

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void use(std::string name);
    Shader* getShader(std::string name) { return _shaderMap[name]; }
    Shader* currentShader() { return _curShader; }

private:
    std::map<std::string, Shader*> _shaderMap;
    Shader* _curShader;
};

SK_END_NAMESPACE

#endif