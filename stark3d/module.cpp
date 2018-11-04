#include "module.h"
#include "effect.h"

SK_BEGIN_NAMESPACE

SceneManager* Module::_sceneManager = NULL;
RenderDevice* Module::_renderDevice = NULL;
ResourceManager* Module::_resourceManager = NULL;

static EffectNormal *gs_effect = NULL;

bool Module::init()
{
//     int test = ogl_LoadFunctions();
//     if (test == ogl_LOAD_FAILED)
//     {
//         printf("err when glload init\n");
//         return 1;
//     }

    if (_sceneManager == NULL) _sceneManager = new SceneManager();
    if (_renderDevice == NULL) _renderDevice = new RenderDevice();
    if (_resourceManager == NULL) _resourceManager = new ResourceManager();

    gs_effect = new EffectNormal;

    return true;
}

void Module::exit()
{
    if (_sceneManager) { delete _sceneManager; _sceneManager = NULL; }
    if (_renderDevice) { delete _renderDevice; _renderDevice = NULL; }
    if (_resourceManager) { delete _resourceManager; _resourceManager = NULL; }

    if (gs_effect) { delete gs_effect; gs_effect = NULL; }
}

void Module::render()
{
    gs_effect->render();

}

SK_END_NAMESPACE
