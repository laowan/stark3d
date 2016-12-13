#include "mesh.h"
#include "module.h"

SK_BEGIN_NAMESPACE

Mesh::Mesh(const std::string& file)
{
    FileLoader3DS loader;
    loader.load(file);

    uint32 num;
    MeshData* meshes;
    loader.getMeshData(&num, &meshes);

    // create vbo
    
    std::vector<float> data;
    std::vector<uint32> indexData;
    for (uint32 i = 0; i < num; i++)
    {
        data.clear();

        uint32 numVertex = meshes[i].numVertices;
        data.reserve(8 * numVertex);
        for (uint32 j = 0; j < numVertex; j++)
        {
            data.push_back(meshes[i].vertices[3*j]);
            data.push_back(meshes[i].vertices[3*j+1]);
            data.push_back(meshes[i].vertices[3*j+2]);

            if (meshes[i].normals)
            {
                data.push_back(meshes[i].normals[3*j]);
                data.push_back(meshes[i].normals[3*j+1]);
                data.push_back(meshes[i].normals[3*j+2]);
            }
            else
            {
                data.push_back(1.0);
                data.push_back(1.0);
                data.push_back(1.0);
            }
            
            if (meshes[i].texcos)
            {
                data.push_back(meshes[i].texcos[2*j]);
                data.push_back(meshes[i].texcos[2*j+1]);
            }
            else
            {
                data.push_back(1.0);
                data.push_back(1.0);
            }
        }

        GLuint bufId;
        glGenBuffers(1, &bufId);
        glBindBuffer(GL_ARRAY_BUFFER, bufId);
        glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), (void*)&data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        _vertexbufs.push_back(bufId);

        indexData.clear();
        for (uint32 k = 0; k < meshes[0].numFaces; k++)
        {
            Facets facets = meshes[0].faces[k];
            if (facets.type == 0)
            {
                for (uint32 m = 0; m < facets.num; m++)
                {
                    indexData.push_back(facets.index[m]);
                }
            }
            else if (facets.type == 1)
            {
            }
            else if (facets.type == 2)
            {
            }
        }

        glGenBuffers(1, &bufId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(int), (void*)&indexData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        _indexbufs.push_back(bufId);
        _indexCounts.push_back(indexData.size());
    }
}

Mesh::~Mesh()
{}

bool Mesh::render(RenderAction* act)
{
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
    return true;
}

SK_END_NAMESPACE

