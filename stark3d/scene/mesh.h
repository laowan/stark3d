#pragma once

#include "global.h"
#include "utils/math.h"

#include <vector>

SK_BEGIN_NAMESPACE

class Mesh
{
public:
    Mesh();
    ~Mesh();

    int getVBO();
    int getIBO();

public:
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector3> tangents;
    std::vector<uint16> indices;

private:
    int _vbo;
    int _ibo;
};

SK_END_NAMESPACE
