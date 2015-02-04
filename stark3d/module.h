#ifndef UTILS_MODULES_H
#define UTILS_MODULES_H

#include "scene.h"
#include "utils/matrix.h"
#include "utils/shadermanager.h"
using Scene::SceneManager;
using Util::ShaderManager;

class Module
{
public:
    static bool init();
    static void exit();

    static SceneManager& sceneMan() { return *_sceneManager; }
    static ShaderManager& shaderMan() { return *_shaderManager; }

private:
    static SceneManager* _sceneManager;
    static ShaderManager* _shaderManager;
};


#endif