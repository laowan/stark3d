#ifndef _SCENE_H
#define _SCENE_H

#include "scene/node.h"
#include "scene/bbox.h"
#include "scene/color.h"
#include "scene/cube.h"
#include "scene/line.h"
#include "scene/terrain.h"
#include "scene/transform.h"
#include "scene/camera.h"
#include "scene/texture.h"

#include "renderaction.h"

SK_BEGIN_NAMESPACE

/*!
    we use this class to 1) construct the scene graph, 2) render the scene.
*/
class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    int addNode(SceneNode* parent, SceneNode* node);
    int addNode(SceneNode* node);
    SceneNode* resolve(int idx);
    bool render(SceneNode* node = NULL);
    void print(SceneNode* node = NULL);
	Camera* getCamera();

private:
    std::vector<SceneNode*> _nodes;
    RenderAction* _renderAct;
	Camera* _cam;
};
SK_END_NAMESPACE
#endif