#ifndef _SCENE_H
#define _SCENE_H

#include <vector>

namespace Scene {

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    virtual bool render();

protected:
    std::vector<SceneNode*> _children;
    int _handle;

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