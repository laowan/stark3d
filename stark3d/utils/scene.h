#ifndef UTILS_SCENE_H
#define UTILS_SCENE_H

#include <vector>

namespace Util {

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    void render();

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
    void render(SceneNode* node = NULL);

private:
    std::vector<SceneNode*> _nodes;

};
}

#endif