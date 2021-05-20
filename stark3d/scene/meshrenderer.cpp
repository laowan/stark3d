#include "scene/meshrenderer.h"
#include "scene/scene.h"
#include "scene/mesh.h"
#include "utils/gldefine.h"

SK_BEGIN_NAMESPACE

void MeshRenderer::fillVertexBuffer(Scene* scene, int materialIndex, std::vector<VertexBuffer>& attribs)
{
    if (_meshId <= 0)
    {
        return;
    }

    Mesh* mesh = scene->getMesh(_meshId);
    int vbo = mesh->getVBO();

    int offset = 0;
    if (mesh->positions.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aPosition";
        attr.size = 3;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector3);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector3) * mesh->positions.size();
    }
    if (mesh->normals.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aNormal";
        attr.size = 3;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector3);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector3) * mesh->normals.size();
    }
    if (mesh->tangents.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aTangent";
        attr.size = 4;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector4);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector4) * mesh->tangents.size();
    }
    if (mesh->uv.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aTextureCoord";
        attr.size = 2;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector2);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector2) * mesh->uv.size();
    }
    if (mesh->uv2.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aTextureCoord1";
        attr.size = 2;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector2);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector2) * mesh->uv2.size();
    }
    if (mesh->colors.size() > 0)
    {
        VertexBuffer attr;
        attr.vbo = vbo;
        attr.name = "aColor";
        attr.size = 4;
        attr.type = GL_FLOAT;
        attr.stride = sizeof(Vector4);
        attr.offset = offset;
        attr.divisor = 0;
        attribs.push_back(attr);
        offset += sizeof(Vector4) * mesh->colors.size();
    }
}

void MeshRenderer::fillIndexBuffer(Scene* scene, int materialIndex, IndexBuffer& indexBuffer)
{
    if (_meshId <= 0)
    {
        return;
    }

    Mesh* mesh = scene->getMesh(_meshId);
    if (materialIndex >= mesh->indices.size())
    {
        materialIndex = 0;
    }

    if (materialIndex >= 0)
    {
        int ibo = mesh->getIBO();
        int offset = 0;

        indexBuffer.ibo = ibo;
        indexBuffer.primitiveMode = GL_TRIANGLES;
        indexBuffer.indexCount = (int)mesh->indices.size();
        indexBuffer.indexType = GL_UNSIGNED_SHORT;
        indexBuffer.indexOffset = offset * sizeof(unsigned short);
    }
}

SK_END_NAMESPACE