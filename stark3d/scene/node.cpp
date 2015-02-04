#include "node.h"

namespace Scene {

// ********************************************************************
// Class SceneNode
// ********************************************************************

SceneNode::SceneNode()
{
    _handle = -1;
}

SceneNode::~SceneNode()
{
    
}

bool SceneNode::render()
{
    return true;
}

BBox SceneNode::boundingBox()
{
    return _boundingBox;
}

}