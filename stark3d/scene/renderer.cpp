#include "scene/renderer.h"
#include "scene/camera.h"
#include "scene/material.h"
#include "graphics/shader.h"
#include "graphics/program.h"

SK_BEGIN_NAMESPACE

void Renderer::render(Camera* camera)
{
    Material* mat = getMaterial();
    render(camera, mat);
}

void Renderer::render(Camera* camera, Material* material)
{
    const Matrix4& vmat = camera->getViewMatrix();
    const Matrix4& pmat = camera->getProjectMatrix();

    material->setMatrix("uMVP", vmat);

    Shader* shader = material->getShader();
    Program* program = shader->getProgram();

    program->use();

    material->applyUniform(program);

    std::vector<VertexBuffer> attribs;
    IndexBuffer indexBuffer;
    fillVertexBuffer(0, attribs);
    fillIndexBuffer(0, indexBuffer);

    for (const auto& i : attribs)
    {
        if (program->getHandle(i.name, false) >= 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, i.vbo);
            program->setVertexAttribPointer(i.name, i.size, i.type, GL_FALSE, i.stride, (void*)(size_t)i.offset);
        }
    }

    if (indexBuffer.ibo > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.ibo);

        if (indexBuffer.indexCount > 0)
        {
            glDrawElements(indexBuffer.primitiveMode, indexBuffer.indexCount, indexBuffer.indexType, (void*)(size_t)indexBuffer.indexOffset);
        }
    }

    for (const auto& i : attribs)
    {
        if (program->getHandle(i.name, false) >= 0)
        {
            program->disableVertexAttrib(i.name);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

SK_END_NAMESPACE