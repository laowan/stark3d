#ifndef _NODE_H
#define _NODE_H

#include "global.h"
#include "BBox.h"
#include <vector>
#include <string>

#include "renderaction.h"

SK_BEGIN_NAMESPACE

class SceneNode
{
public:
    SceneNode() : _handle(-1), _current(-1) {}
    virtual ~SceneNode() {}

    virtual bool renderEnter(RenderAction* act) { return true; }
    virtual bool render(RenderAction* act) { return true; }
    virtual bool renderLeave(RenderAction* act) { return true; }

    virtual BBox boundingBox() { return _boundingBox; }
    virtual std::string type() { return "SceneNode"; }
    void print(std::string prefix = "");

protected:
    std::vector<SceneNode*> _children;
    int _handle;
    int _current;  // used in traversal procedure
    BBox _boundingBox;

    friend class SceneManager;

};

SK_END_NAMESPACE

#endif