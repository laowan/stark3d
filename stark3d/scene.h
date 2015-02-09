#ifndef _SCENE_H
#define _SCENE_H

#include "scene/node.h"
#include "scene/bbox.h"
#include "scene/color.h"
#include "scene/cube.h"
#include "scene/line.h"
#include "scene/terrain.h"

SK_BEGIN_NAMESPACE
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

private:
    std::vector<SceneNode*> _nodes;
};
SK_END_NAMESPACE
#endif