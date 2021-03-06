#pragma once

#include "global.h"
#include "scene/component.h"
#include <vector>
#include <string>

SK_BEGIN_NAMESPACE

class Camera;
class Material;
class Component;
class Scene;
class Renderer : public Component
{
public:
    struct VertexBuffer
    {
        int vbo = 0;
        std::string name;
        int size = 0;
        int type = 0;
        int stride = 0;
        int offset = 0;
        int divisor = 0;
    };

    struct IndexBuffer
    {
        int ibo = 0;
        int primitiveMode = 0;
        int indexCount = 0;
        int indexType = 0;
        int indexOffset = 0;
    };

    virtual void render(Camera* camera, Scene* scene);
    virtual void render(Camera* camera, Material* mat, Scene* scene);

    void setMaterialId(int materialId) { _materialId = materialId; }
    int getMaterialId() { return _materialId; }

    virtual void fillVertexBuffer(Scene* scene, int materialIndex, std::vector<VertexBuffer>& attribs) = 0;
    virtual void fillIndexBuffer(Scene* scene, int materialIndex, IndexBuffer& indexBuffer) = 0;

private:
    int _materialId;
};

SK_END_NAMESPACE