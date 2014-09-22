#include "shadermanager.h"

namespace Util { namespace Shader {

void ShaderManager::use(ShaderType type)
{
    std::map<ShaderType, Shader*>::iterator it = _shaderMap.find(type);
    if (it == _shaderMap.end())
    {
        Shader* shader;
        switch (type)
        {
        case SD_NORMAL:
            shader = new Shader();
            break;
        }

        shader->use();
        _shaderMap[type] = shader;
    }
    else
    {
        _shaderMap[type]->use();
    }
}

} }