#include "shadermanager.h"

SK_BEGIN_NAMESPACE

ShaderManager::ShaderManager() : _curShader(NULL)
{

}

ShaderManager::~ShaderManager()
{

}

void ShaderManager::use(ShaderType type)
{
    std::map<ShaderType, Shader*>::iterator it = _shaderMap.find(type);
    if (it == _shaderMap.end())
    {
        Shader* shader = NULL;
        switch (type)
        {
        case SD_NORMAL:
            shader = new Shader("normal");
            break;
        }

        if (shader)
        {
            shader->use();
            _shaderMap[type] = shader;
            _curShader = shader;
        }
    }
    else
    {
        _shaderMap[type]->use();
        _curShader = _shaderMap[type];
    }
}

SK_END_NAMESPACE