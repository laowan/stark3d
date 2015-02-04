#include "module.h"

SceneManager* Module::_sceneManager = NULL;
ShaderManager* Module::_shaderManager = NULL;

bool Module::init()
{
    if (_sceneManager == NULL) _sceneManager = new SceneManager();
    if (_shaderManager == NULL) _shaderManager = new ShaderManager();
    return true;
}

void Module::exit()
{
    if (_sceneManager) { delete _sceneManager; _sceneManager = NULL; }
    if (_shaderManager) { delete _shaderManager; _shaderManager = NULL; }
}
