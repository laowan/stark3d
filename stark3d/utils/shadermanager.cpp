#include "shadermanager.h"

SK_BEGIN_NAMESPACE

ShaderManager::ShaderManager() : _curShader(NULL)
{

}

ShaderManager::~ShaderManager()
{

}

void ShaderManager::use(std::string name)
{
    std::map<std::string, Shader*>::iterator it = _shaderMap.find(name);
    if (it == _shaderMap.end())
    {
        Shader* shader = new Shader(name);
        if (shader)
        {
            shader->use();
            _shaderMap[name] = shader;
            _curShader = shader;
        }
    }
    else
    {
        _shaderMap[name]->use();
        _curShader = _shaderMap[name];
    }
}

SK_END_NAMESPACE
