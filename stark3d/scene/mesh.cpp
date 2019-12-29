#include "mesh.h"
#include "utils/renderdevice.h"
#include "utils/gldefine.h"
#include "utils/shader.h"

SK_BEGIN_NAMESPACE

Mesh::Mesh(const aiMesh* mesh)
{
    // create vbo
    uint32 numVertex = mesh->mNumVertices;
    GLuint bufId;
    glGenBuffers(1, &bufId);
    glBindBuffer(GL_ARRAY_BUFFER, bufId);
    glBufferData(GL_ARRAY_BUFFER, numVertex * sizeof(aiVector3D), (void*)mesh->mVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _vertexbuf = bufId;

    glGenBuffers(1, &bufId);
    glBindBuffer(GL_ARRAY_BUFFER, bufId);
    glBufferData(GL_ARRAY_BUFFER, numVertex * sizeof(aiVector3D), (void*)mesh->mNormals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _normalBuf = bufId;

    std::vector<unsigned int> ids;
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (int n = 0; n < face.mNumIndices; n++)
        {
            ids.push_back(face.mIndices[n]);
        }
    }

    glGenBuffers(1, &bufId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ids.size() * sizeof(unsigned int), (void*)&ids[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    _indexbuf = bufId;
    _indexCount = ids.size();
}

Mesh::~Mesh()
{
    if (_vertexbuf)
    {
        glDeleteBuffers(1, &_vertexbuf);
        _vertexbuf = 0;
    }

    if (_normalBuf)
    {
        glDeleteBuffers(1, &_normalBuf);
        _normalBuf = 0;
    }

    if (_indexbuf)
    {
        glDeleteBuffers(1, &_indexbuf);
        _indexbuf = 0;
    }
}

bool Mesh::render(Shader* shader, mat4x4 mvpMat, RenderDevice* device)
{
    shader->use();

    ShaderUniforms& uniforms = shader->uniforms();

    mat4x4_dup(uniforms.mvp, mvpMat);

    shader->commitUniforms();

    uint32 stride(sizeof(float) * 3);
    device->setVertexBuffer(_vertexbuf);
    device->setVertexLayout(0, stride, 0);

    device->setVertexBuffer(_normalBuf);
    device->setVertexLayout(1, stride, 0);

    device->setIndexBuffer(_indexbuf);

    device->draw(SK::PRIM_TRIANGLES, _indexCount);

    device->setVertexBuffer(0);
    device->setIndexBuffer(0);

    return true;
}

SK_END_NAMESPACE

