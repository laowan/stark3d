#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "BBox.h"

namespace Scene {

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    virtual bool render();
    virtual BBox boundingBox();

protected:
    std::vector<SceneNode*> _children;
    int _handle;
    BBox _boundingBox;

    friend class SceneManager;

};

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    int addNode(SceneNode* parent, SceneNode* node);
    int addNode(SceneNode* node);
    bool render(SceneNode* node = NULL);

private:
    std::vector<SceneNode*> _nodes;

};
}

#endif