#include "line.h"
#include "module.h"
#include <glload/gl_3_3.h>

SK_BEGIN_NAMESPACE

Line::Line(glm::vec3& point1, glm::vec3& point2) : _vb(0)
{
    float data[6];
    data[0] = point1.x; data[1] = point1.y; data[2] = point1.z;
    data[3] = point2.x; data[4] = point2.y; data[5] = point2.z;

    glGenBuffers(1, (GLuint*)&_vb);
    glBindBuffer(GL_ARRAY_BUFFER, _vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line::~Line()
{
    if (_vb) { glDeleteBuffers(1, (GLuint*)&_vb); _vb = 0; }
}

bool Line::render(RenderAction* act)
{
    Shader* shader = Module::shaderMan().currentShader();
    ShaderUniforms& uniforms = shader->uniforms();
    uniforms.mvp *= act->_modelMat.glMatrix();
    uniforms.color = act->_color;
    shader->commitUniforms();

    glBindBuffer(GL_ARRAY_BUFFER, _vb);

    glEnableVertexAttribArray(0);

    int stride(sizeof(float)* 3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    glDrawArrays(GL_LINES, 0, 2);

    glDisableVertexAttribArray(0);

    return true;
}

void Line::reset(glm::vec3& point1, glm::vec3& point2)
{
    if (_vb) { glDeleteBuffers(1, (GLuint*)&_vb); _vb = 0; }

    float data[6];
    data[0] = point1.x; data[1] = point1.y; data[2] = point1.z;
    data[3] = point2.x; data[4] = point2.y; data[5] = point2.z;

    glGenBuffers(1, (GLuint*)&_vb);
    glBindBuffer(GL_ARRAY_BUFFER, _vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SK_END_NAMESPACE