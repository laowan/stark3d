#ifndef _NODE_H
#define _NODE_H

#include "global.h"
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


}

#endif