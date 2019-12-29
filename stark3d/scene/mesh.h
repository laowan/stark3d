#ifndef SCENE_MESH_H
#define SCENE_MESH_H

#include "global.h"
#include "assimp/mesh.h"
#include "utils/linmath.h"

#include <vector>

SK_BEGIN_NAMESPACE

class Shader;
class RenderDevice;
class Mesh
{
public:
    Mesh(const aiMesh* mesh);
    ~Mesh();

    bool render(Shader* shader, mat4x4 mvpMat, RenderDevice* device);
private:
    uint32 _vertexbuf;
    uint32 _normalBuf;
    uint32 _indexbuf;
    uint32 _indexCount;
};

SK_END_NAMESPACE

#endif
