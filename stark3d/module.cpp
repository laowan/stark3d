#include "module.h"

SK_BEGIN_NAMESPACE

SceneManager* Module::_sceneManager = NULL;
ShaderManager* Module::_shaderManager = NULL;
RenderDevice* Module::_renderDevice = NULL;

bool Module::init()
{
    int test = ogl_LoadFunctions();
    if (test == ogl_LOAD_FAILED)
    {
        printf("err when glload init\n");
        return 1;
    }

    if (_sceneManager == NULL) _sceneManager = new SceneManager();
    if (_shaderManager == NULL) _shaderManager = new ShaderManager();
    if (_renderDevice == NULL) _renderDevice = new RenderDevice();
    return true;
}

void Module::exit()
{
    if (_sceneManager) { delete _sceneManager; _sceneManager = NULL; }
    if (_shaderManager) { delete _shaderManager; _shaderManager = NULL; }
    if (_renderDevice) { delete _renderDevice; _renderDevice = NULL; }
}

SK_END_NAMESPACE
