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

class SceneManagerImpl : public Impl<SceneManager>
{
public:
    void init();
    void exit();

    std::vector<SceneNode*> _nodes;
    RenderAction* _renderAct;
    Camera* _cam;
    Box* _boxList;
    Box* _pickedBox;
    Line* _pickLine;
};

void SceneManagerImpl::init()
{
    _renderAct = new RenderAction();

    SceneNode* root = new SceneNode();
    _nodes.push_back(root);

    //root->_handle = 1;

    _cam = new Camera();

    _pickLine = new Line;
    _boxList = NULL;
    _pickedBox = NULL;
}

void SceneManagerImpl::exit()
{
    for (SceneNode* node : _nodes)
        delete node;

    if (_cam)
        delete _cam;

    if (_renderAct)
        delete _renderAct;

    Box *curBox = _boxList;
    while (curBox)
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

SceneManager::SceneManager()
{
    SK_I(SceneManager);

    d->init();
    d->_nodes[0]->_handle = 1;
}

SceneManager::~SceneManager()
{
    SK_E(SceneManager);
    d->exit();
}

int SceneManager::addNode(SceneNode* parent, SceneNode* node)
{
    SK_D(SceneManager);
    parent->_children.push_back(node);
    d->_nodes.push_back(node);

    node->_handle = (int)d->_nodes.size();
    return (int)d->_nodes.size();
}

int SceneManager::addNode(SceneNode* node)
{
    SK_D(SceneManager);
    d->_nodes[0]->_children.push_back(node);
    d->_nodes.push_back(node);

    node->_handle = (int)d->_nodes.size();
    return (int)d->_nodes.size();
}

void SceneManager::clear()
{
    SK_D(SceneManager);
    size_t sz = d->_nodes.size();
    for (size_t i = 0; i < sz; i++)
        delete d->_nodes[i];

    d->_nodes.clear();

    SceneNode* root = new SceneNode();
    d->_nodes.push_back(root);

    root->_handle = 1;
}

SceneNode* SceneManager::resolve(int idx)
{
    SK_D(SceneManager);
    if (idx < 1 || idx > (int)d->_nodes.size())
        return NULL;
    return d->_nodes.at(idx-1);
}

bool SceneManager::render()
{
    SK_D(SceneManager);
    renderNode(NULL);

    return true;

    // render the picked box
    if (d->_pickedBox)
    {
        Cube cube(1.0);
        d->_renderAct->_color = glm::vec4(d->_pickedBox->r/255.0, d->_pickedBox->g/255.0, d->_pickedBox->b/255.0, 1.0);
        Transform transform = Transform();
        Matrix& mat = transform.matrix();
        mat.pan(d->_pickedBox->x, d->_pickedBox->y, d->_pickedBox->z);
        transform.renderEnter(d->_renderAct);
        Cube(1.0).render(d->_renderAct);
        transform.renderLeave(d->_renderAct);
    }

    d->_renderAct->_color = glm::vec4(0.0, 0.0, 0.0, 1.0);
    d->_pickLine->render(d->_renderAct);

    return true;
}

bool SceneManager::renderNode(SceneNode* node /*= NULL*/)
{
    SK_D(SceneManager);
    if (node == NULL)
        node = d->_nodes[0];

    // reset the states
    d->_renderAct->reset();

    stack<int> nodeStack;
    nodeStack.push(node->_handle);
    node->renderEnter(d->_renderAct);
    while (node->_children.size() > 0)
    {
        node->_current = 0;
        node = node->_children[0];
        nodeStack.push(node->_handle);
        node->renderEnter(d->_renderAct);
    }

    while (!nodeStack.empty())
    {
        int topIdx = nodeStack.top();
        node = d->_nodes[nodeStack.top()-1];
        size_t childCount = node->_children.size();
        if (childCount > 0)
        {
            if (node->_current + 1 < childCount)
            {
                SceneNode* newNode = node->_children[node->_current+1];
                newNode->_current = -1;
                nodeStack.push(newNode->_handle);
                newNode->renderEnter(d->_renderAct);
                node->_current++;
            }
            else
            {
                node->render(d->_renderAct);
                node->renderLeave(d->_renderAct);
                nodeStack.pop();
            }
        }
        else
        {
            node->render(d->_renderAct);
            node->renderLeave(d->_renderAct);
            nodeStack.pop();
        }
    }

    return true;
}

void SceneManager::print(SceneNode* node)
{
    SK_D(SceneManager);
    if (node == NULL)
        node = d->_nodes[0];
    node->print();
}

Camera* SceneManager::getCamera()
{
    SK_D(SceneManager);
    return d->_cam;
}

int SceneManager::addBox(int32 x, int32 y, int32 z, uint8 r, uint8 g, uint8 b)
{
    SK_D(SceneManager);
    Box *box = new Box;
    box->x = x; box->y = y; box->z = z;
    box->r = r; box->g = g; box->b = b;
    box->next = NULL;

    Box *lastBox = d->_boxList;
    if (!lastBox) 
    {
        d->_boxList = box;
        d->_boxList->next = NULL;
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
    
    addNode(resolve(idx), new Texture());
    addNode(resolve(idx), new Cube(1.0));
    return 1;
}

bool SceneManager::renderBox(Box* box)
{

    return true;
}

BBox SceneManager::boundingBox()
{
    SK_D(SceneManager);
    BBox bbox;
    Box *curBox = d->_boxList;
    while (curBox)
    {
        bbox.add((float)(curBox->x + 0.5), (float)(curBox->y + 0.5), (float)(curBox->z + 0.5));
        bbox.add((float)(curBox->x - 0.5), (float)(curBox->y - 0.5), (float)(curBox->z - 0.5));
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

bool SceneManager::pick(int x, int y)
{
    SK_D(SceneManager);
    Viewport& vport = d->_cam->getViewport();
    Point2 vpnt;
    vpnt.x = (float)(( x - vport.pixWidth / 2.0 ) / vport.pixScale);
    vpnt.y = (float)(( vport.pixHeight / 2.0 - y) / vport.pixScale);

    glm::vec4 vec(vpnt.x, vpnt.y, 100.0, 1.0);
    glm::vec4 linePnt = d->_cam->getViewMatrix().glMatrix() * vec;

    printf("%f, %f, %f\n", linePnt.x, linePnt.y, linePnt.z);
    glm::vec4 vec1(0.0, 0.0, 0.0, 1.0);
    glm::vec4 dirPnt1 = d->_cam->getViewMatrix().glMatrix() * vec1;

    glm::vec4 vec2(0.0, 0.0, -1.0, 1.0);
    glm::vec4 dirPnt2 = d->_cam->getViewMatrix().glMatrix() * vec2;

    glm::vec4 dir = dirPnt2 - dirPnt1;

    // reset pick line and render it later for debug purpose
    glm::vec3 linePnt1 = glm::vec3(linePnt.x, linePnt.y, linePnt.z);
    glm::vec4 linePnt2 = linePnt + 1000 * dir;
    d->_pickLine->reset(linePnt1, glm::vec3(linePnt2.x, linePnt2.y, linePnt2.z));

    if (d->_pickedBox) { delete d->_pickedBox; d->_pickedBox = NULL; }

    Box *curBox = d->_boxList;
    Point3 crossPnt;
    double depth = -BBOX_LIMIT;
    while (curBox)
    {
        BBox bbox;
        bbox.add((float)(curBox->x + 0.5), (float)(curBox->y + 0.5), (float)(curBox->z + 0.5));
        bbox.add((float)(curBox->x - 0.5), (float)(curBox->y - 0.5), (float)(curBox->z - 0.5));

        if (isPicked(Point3(vpnt.x, vpnt.y, 0.0), Point3(dir.x, dir.y, dir.z), &bbox, &crossPnt))
        {
            glm::vec4 tmpPnt(crossPnt.x, crossPnt.y, crossPnt.z, 1.0);
            glm::vec4 viewPnt = d->_cam->getViewMat() * tmpPnt;

            if (viewPnt.z > depth)
            {
                if (!d->_pickedBox)
                {
                    d->_pickedBox = new Box;
                    d->_pickedBox->r = 255;
                    d->_pickedBox->g = 255;
                    d->_pickedBox->b = 255;
                }                    
                d->_pickedBox->x = curBox->x;
                d->_pickedBox->y = curBox->y;
                d->_pickedBox->z = curBox->z;

                depth = viewPnt.z;
            }
        }
        curBox = curBox->next;
    }

    return true;
}

/*!
    line:
        x = lpx + dirx * t,
        y = lpy + diry * t,  (1)
        z = lpz + dirz * t,
    plane:
        nx * (x - px) + ny * (y - py) + nz * (z - pz) = 0;  (2)

    from (1)(2), get the value of t,
    then form (1), get the cross point.

*/
bool SceneManager::isPicked(Point3 linePnt, Point3 lineDir, BBox* bbox, Point3* crsPnt)
{
    Point3 maxPnt = bbox->maxPoint();
    Point3 minPnt = bbox->minPoint();

    Point3 planePnts[6];
    Point3 planeNormal[6];
    bbox->getSixPlanes(planePnts, planeNormal);
    
    Point3 crossPnt;
    for (int i = 0; i < 6; i++)
    {
        float tmp = lineDir.x * planeNormal[i].x +
            lineDir.y * planeNormal[i].y +
            lineDir.z * planeNormal[i].z;
        if (tmp < -0.0001 || tmp > 0.0001) // not zero
        {
            float t = (planePnts[i].x - linePnt.x) * planeNormal[i].x +
                (planePnts[i].y - linePnt.y) * planeNormal[i].y +
                (planePnts[i].z - linePnt.z) * planeNormal[i].z;
            t /= tmp;

            crossPnt.x = linePnt.x + lineDir.x * t;
            crossPnt.y = linePnt.y + lineDir.y * t;
            crossPnt.z = linePnt.z + lineDir.z * t;

            if (crossPnt.x < maxPnt.x + 0.0001 && crossPnt.x > minPnt.x - 0.0001 &&
                crossPnt.y < maxPnt.y + 0.0001 && crossPnt.y > minPnt.y - 0.0001 &&
                crossPnt.z < maxPnt.z + 0.0001 && crossPnt.z > minPnt.z - 0.0001)
            {
                crsPnt->x = crossPnt.x;
                crsPnt->y = crossPnt.y;
                crsPnt->z = crossPnt.z;
                return true;
            }
        }
    }

    return false;
}

SK_END_NAMESPACE
