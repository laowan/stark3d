#include "shadermanager.h"

namespace Util {

void ShaderManager::use(ShaderType type)
{
    std::map<ShaderType, Shader*>::iterator it = _shaderMap.find(type);
    if (it == _shaderMap.end())
    {
        Shader* shader = NULL;
        switch (type)
        {
        case SD_NORMAL:
            shader = new Shader();
            break;
        }

        if (shader)
        {
            shader->use();
            _shaderMap[type] = shader;
        }
    }
    else
    {
        _shaderMap[type]->use();
    }
}

}