#ifndef UTILS_MODULES_H
#define UTILS_MODULES_H

namespace Util {

class SceneManager;

class Modules
{
public:
    static bool init();
    static void exit();

    static SceneManager& sceneManager() { return *_sceneManager; }

private:
    static SceneManager* _sceneManager;
};

}

#endif