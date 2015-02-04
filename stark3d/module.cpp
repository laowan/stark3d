#include "module.h"

SceneManager* Module::_sceneManager = NULL;
ShaderManager* Module::_shaderManager = NULL;

bool Module::init()
{
    if (_sceneManager == NULL) _sceneManager = new SceneManager();
    return true;
}

void Module::exit()
{
    if (_sceneManager)
    {
        delete _sceneManager;
        _sceneManager = NULL;
    }
}
