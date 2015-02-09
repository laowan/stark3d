#ifndef _NODE_H
#define _NODE_H

#include "global.h"
#include "BBox.h"
#include <vector>
#include <string>
#include <iostream>

SK_BEGIN_NAMESPACE

class SceneNode
{
public:
    SceneNode() : _handle(-1), _current(-1) {}
    ~SceneNode() {}

    virtual bool renderEnter()
                {
                std::cout << _handle << " enter" << std::endl;
                return true;
                }
    virtual bool render() { return true; }
    virtual bool renderLeave()
                {
                std::cout << _handle << " leave" << std::endl;
                return true;
                }

    virtual BBox boundingBox() { return _boundingBox; }
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