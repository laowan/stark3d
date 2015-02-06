#ifndef _NODE_H
#define _NODE_H

#include "global.h"
#include "BBox.h"
#include <vector>
#include <string>

namespace Scene {

class SceneNode
{
public:
    SceneNode() : _handle(-1) {}
    ~SceneNode() {}

    virtual bool render() { return true; }
    virtual BBox boundingBox() { return _boundingBox; }
    void print(std::string prefix = "");

protected:
    std::vector<SceneNode*> _children;
    int _handle;
    BBox _boundingBox;

    friend class SceneManager;

};

}

#endif