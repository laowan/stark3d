#include "modules.h"
#include "scene.h"

namespace Util {

SceneManager* Modules::_sceneManager = NULL;

bool Modules::init()
{
    if (_sceneManager == NULL) _sceneManager = new SceneManager();
    return true;
}

void Modules::exit()
{
    if (_sceneManager)
    {
        delete _sceneManager;
        _sceneManager = NULL;
    }
}

}