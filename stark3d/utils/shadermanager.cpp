#include "shadermanager.h"
#include <map>

SK_BEGIN_NAMESPACE

class ShaderManagerImpl : public Impl<ShaderManager>
{
public:
    std::map<std::string, Shader*> _shaderMap;
    Shader* _curShader;
};

ShaderManager::ShaderManager()
{
    SK_I(ShaderManager);
    d->_curShader = NULL;
}

ShaderManager::~ShaderManager()
{
    SK_E(ShaderManager);
}

void ShaderManager::use(std::string name)
{
    SK_D(ShaderManager);
    auto it = d->_shaderMap.find(name);
    if (it == d->_shaderMap.end())
    {
        Shader* shader = new Shader(name);
        if (shader)
        {
            shader->use();
            d->_shaderMap[name] = shader;
            d->_curShader = shader;
        }
    }
    else
    {
        d->_shaderMap[name]->use();
        d->_curShader = d->_shaderMap[name];
    }
}

Shader* ShaderManager::getShader(std::string name)
{
    SK_D(ShaderManager);
    auto it = d->_shaderMap.find(name);
    if (it == d->_shaderMap.end())
    {
        Shader* shader = new Shader(name);
        d->_shaderMap[name] = shader;
    }
    return d->_shaderMap[name]; 
}

Shader* ShaderManager::currentShader() 
{
    SK_D(ShaderManager);
    return d->_curShader; 
}

SK_END_NAMESPACE
