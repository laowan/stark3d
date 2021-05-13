#ifndef SCENE_MESH_H
#define SCENE_MESH_H

#include "global.h"
#include "utils/math.h"

#include <vector>

SK_BEGIN_NAMESPACE

class Mesh
{
public:
    Mesh();
    ~Mesh();

public:
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector3> tangents;
    std::vector<uint16> indices;
};

SK_END_NAMESPACE

#endif
