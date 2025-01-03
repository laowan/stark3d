#ifndef _SCENE_H
#define _SCENE_H

#include "scene/node.h"
#include "scene/bbox.h"
#include "scene/color.h"
#include "scene/cube.h"
#include "scene/line.h"
#include "scene/terrain.h"
#include "scene/transform.h"
#include "scene/camera.h"
#include "scene/texture.h"
#include "scene/bsp.h"
#include "scene/mesh.h"
#include "scene/sprite.h"
#include "scene/particle.h"

#include "renderaction.h"

SK_BEGIN_NAMESPACE

typedef struct _Box
{
    int32 x;
    int32 y;
    int32 z;
    uint8 r;
    uint8 g;
    uint8 b;
    struct _Box *next;
} Box;

/*!
    we use this class to 1) construct the scene graph, 2) render the scene.
*/
class STARK_API SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    int addNode(SceneNode* parent, SceneNode* node);
    int addNode(SceneNode* node);

    void clear();

    SceneNode* resolve(int idx);
    bool render();
    bool renderNode(SceneNode* node = NULL);
    void print(SceneNode* node = NULL);
    Camera* getCamera();
    
    int addBox(int32 x, int32 y, int32 z, uint8 r, uint8 g, uint8 b);
    bool renderBox(Box* box);
    BBox boundingBox();

    bool open(const std::string& path);
    bool save(const std::string& path);

    bool pick(int x, int y);
    bool isPicked(Point3 linePnt, Point3 lineDir, BBox* bbox, Point3* crsPnt);

private:
    SK_DECLARE_IMPL(SceneManager);
};
SK_END_NAMESPACE
#endif