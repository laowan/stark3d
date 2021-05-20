#pragma once

#include "renderer.h"

SK_BEGIN_NAMESPACE

class MeshRenderer : public Renderer
{
public:
    void fillVertexBuffer(Scene* scene, int materialIndex, std::vector<VertexBuffer>& attribs);
    void fillIndexBuffer(Scene* scene, int materialIndex, IndexBuffer& indexBuffer);

    void setMeshId(int id) { _meshId = id; }

private:
    int _meshId;
};

SK_END_NAMESPACE