#ifndef SCENE_MESH_H
#define SCENE_MESH_H

#include "node.h"

SK_BEGIN_NAMESPACE

class Mesh : public SceneNode
{
public:
    Mesh(const std::string& file);
    ~Mesh();

    bool render(RenderAction* act);
private:
    std::vector<uint32> _vertexbufs;
    std::vector<uint32> _indexbufs;
    std::vector<uint32> _indexCounts;
};

SK_END_NAMESPACE

#endif
