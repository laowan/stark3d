#include "mesh.h"
#include "utils/gldefine.h"

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
{}

bool Mesh::render()
{
    /*
    Shader* shader = Module::resMan().currentShader();
    ShaderUniforms& uniforms = shader->uniforms();
    glm::mat4 saveMvpMat = uniforms.mvp;
    glm::mat4 saveMvMat = uniforms.mv;

    uniforms.mv *= act->_modelMat.glMatrix();
    uniforms.mvp *= act->_modelMat.glMatrix();
    uniforms.color = act->_color;
    uniforms.activeTexture = act->_activeTexture;
    shader->commitUniforms();

    for (size_t i = 0; i < _vertexbufs.size(); i++)
    {
        Module::renderDev().setVertexBuffer(_vertexbufs[i]);
        Module::renderDev().setIndexBuffer(_indexbufs[i]);

        uint32 stride(sizeof(float)* 3 + sizeof(float)* 3 + sizeof(float)* 2);
        Module::renderDev().setVertexLayout(0, stride, 0);
        Module::renderDev().setVertexLayout(1, stride, (const void*)(3 * sizeof(float)));
        Module::renderDev().setVertexLayout(2, stride, (const void*)(6 * sizeof(float)));
        Module::renderDev().draw(SK::PRIM_TRIANGLES, _indexCounts[i]);

        Module::renderDev().setVertexBuffer(0);
        Module::renderDev().setIndexBuffer(0);
    }

    uniforms.mvp = saveMvpMat;
    uniforms.mv = saveMvMat;
    */
    return true;
}

SK_END_NAMESPACE

