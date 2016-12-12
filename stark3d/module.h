#ifndef UTILS_MODULES_H
#define UTILS_MODULES_H

#include <glload/gl_3_3_comp.h>
#include <glload/gl_load.h>
#include "global.h"
#include "scene.h"
#include "utils/utils.h"
#include "utils/matrix.h"
#include "utils/shadermanager.h"
#include "utils/renderdevice.h"
#include "utils/loader.h"

SK_BEGIN_NAMESPACE

class STARK_API Module
{
public:
    static bool init();
    static void exit();
    static void render();

    static SceneManager& sceneMan() { return *_sceneManager; }
    static ShaderManager& shaderMan() { return *_shaderManager; }
    static RenderDevice& renderDev() { return *_renderDevice; }

private:
    static SceneManager* _sceneManager;
    static ShaderManager* _shaderManager;
    static RenderDevice* _renderDevice;
};

SK_END_NAMESPACE

#endif