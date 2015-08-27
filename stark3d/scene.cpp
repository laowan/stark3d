#include "scene.h"
#include <sstream>
#include <iostream>
#include <fstream>
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

	_cam = new Camera();
	addNode(_cam);

    _boxList = NULL;
}

SceneManager::~SceneManager()
{
    for (SceneNode* node : _nodes)
        delete node;

    if (_renderAct)
        delete _renderAct;

    Box *curBox = _boxList;
    while(curBox)
    {
        if (curBox->next)
        {
            _boxList = curBox->next;
            delete curBox;
            curBox = _boxList;
        }
        else
        {
            delete curBox;
            curBox = NULL;
        }
    }

    _boxList = NULL;
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
    node->renderEnter(_renderAct);
    while (node->_children.size() > 0)
    {
        node->_current = 0;
        node = node->_children[0];
        nodeStack.push(node->_handle);
        node->renderEnter(_renderAct);
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
                newNode->renderEnter(_renderAct);
                node->_current++;
            }
            else
            {
                node->render(_renderAct);
                node->renderLeave(_renderAct);
                nodeStack.pop();
            }
        }
        else
        {
            node->render(_renderAct);
            node->renderLeave(_renderAct);
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

Camera* SceneManager::getCamera()
{
	return _cam;
}

int SceneManager::addBox(int32 x, int32 y, int32 z, uint8 r, uint8 g, uint8 b)
{
    Box *box = new Box;
    box->x = x; box->y = y; box->z = z;
    box->r = r; box->g = g; box->b = b;
    box->next = NULL;

    Box *lastBox = _boxList;
    if (!lastBox) 
    {
        _boxList = box;
        _boxList->next = NULL;
    }
    else
    {
        while(lastBox->next != NULL)
            lastBox = lastBox->next;
        lastBox->next = box;
    }

    addNode(new Color(r/255.0, g/255.0, b/255.0, 1.0));

    Transform* transform = new Transform();
    Matrix& mat = transform->matrix();
    mat.pan(x, y, z);
    int idx = addNode(transform);
    
    //addNode(new Texture());
    addNode(resolve(idx), new Cube(1.0));
    return 1;
}

bool SceneManager::renderBox(Box* box)
{
    return true;
}

BBox SceneManager::boundingBox()
{
	BBox bbox;
	Box *curBox = _boxList;
	while (curBox)
	{
		bbox.add(curBox->x + 1, curBox->y + 1, curBox->z + 1);
		bbox.add(curBox->x - 1, curBox->y - 1, curBox->z - 1);
		curBox = curBox->next;
	}

	return bbox;
}

bool SceneManager::open(const std::string& path)
{
    ifstream file(path);
    if (!file) return false;

    std::string line;
    int32 x, y, z;
    int32 r, g, b;
    std::stringstream stream;
    while (getline(file, line))
    {
        sscanf_s(line.c_str(), "%d,%d,%d,%d,%d,%d", &x, &y, &z, &r, &g, &b);
        cout << x << y << z << r << g << b << endl;
        addBox(x, y, z, (uint8)r, (uint8)g, (uint8)b);
    }
    return true;
}

bool SceneManager::save(const std::string& path)
{
    return true;
}

SK_END_NAMESPACE
