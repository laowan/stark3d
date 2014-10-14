#include "scene.h"

namespace Util {

// *********************************************************************************
// Class SceneNode
// *********************************************************************************

SceneNode::SceneNode()
{
    _handle = -1;
}

SceneNode::~SceneNode()
{
    
}

void SceneNode::render()
{
    printf("%d\n", _handle);
}

// *********************************************************************************
// Class SceneManager
// *********************************************************************************

SceneManager::SceneManager()
{
    SceneNode* root = new SceneNode();
    _nodes.push_back(root);

    root->_handle = 1;
}

SceneManager::~SceneManager()
{
    for (SceneNode* node : _nodes)
        delete node;
}

int SceneManager::addNode(SceneNode* parent, SceneNode* node)
{
    parent->_children.push_back(node);
    _nodes.push_back(node);

    node->_handle = (int)_nodes.size();
    return (int)_nodes.size();
}

int SceneManager::addNode(SceneNode* node)
{
    _nodes[0]->_children.push_back(node);
    _nodes.push_back(node);

    node->_handle = (int)_nodes.size();
    return (int)_nodes.size();
}

void SceneManager::render(SceneNode* node /*= NULL*/)
{
    if (node == NULL)
        node = _nodes[0];


    if (node->_children.size() > 0)
    {
        for (SceneNode* child : node->_children)
        {
            render(child);
        }
        node->render();
    }
    else
    {
        node->render();
    }
}

}