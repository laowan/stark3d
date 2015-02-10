#include "scene.h"

#include <stack>
using namespace std;

SK_BEGIN_NAMESPACE

// ********************************************************************
// Class SceneManager
// ********************************************************************

SceneManager::SceneManager()
{
    _renderAct = new RenderAction();

    SceneNode* root = new SceneNode();
    _nodes.push_back(root);

    root->_handle = 1;
}

SceneManager::~SceneManager()
{
    for (SceneNode* node : _nodes)
        delete node;

    if (_renderAct)
        delete _renderAct;
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

SceneNode* SceneManager::resolve(int idx)
{
    if (idx < 1 || idx > (int)_nodes.size())
        return NULL;
    return _nodes.at(idx-1);
}

bool SceneManager::render(SceneNode* node /*= NULL*/)
{
    if (node == NULL)
        node = _nodes[0];

    // reset the states
    _renderAct->reset();

    stack<int> nodeStack;
    nodeStack.push(node->_handle);
    node->renderEnter();
    while (node->_children.size() > 0)
    {
        node->_current = 0;
        node = node->_children[0];
        nodeStack.push(node->_handle);
        node->renderEnter();
    }

    while (!nodeStack.empty())
    {
        int topIdx = nodeStack.top();
        node = _nodes[nodeStack.top()-1];
        size_t childCount = node->_children.size();
        if (childCount > 0)
        {
            if (node->_current + 1 < childCount)
            {
                SceneNode* newNode = node->_children[node->_current+1];
                newNode->_current = -1;
                nodeStack.push(newNode->_handle);
                newNode->renderEnter();
                node->_current++;
            }
            else
            {
                node->render(_renderAct);
                node->renderLeave();
                nodeStack.pop();
            }
        }
        else
        {
            node->render(_renderAct);
            node->renderLeave();
            nodeStack.pop();
        }
    }

    return true;
}

void SceneManager::print(SceneNode* node)
{
    if (node == NULL)
        node = _nodes[0];
    node->print();
}

SK_END_NAMESPACE
