#include "renderdevice.h"

SK_BEGIN_NAMESPACE

RenderDevice::RenderDevice()
{}

RenderDevice::~RenderDevice()
{}

uint32 RenderDevice::createVertexBuffer(uint32 size, const void* data)
{
    uint32 buf;
    glGenBuffers(1, (GLuint*)&buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buf;
}

uint32 RenderDevice::createIndexBuffer(uint32 size, const void* data)
{
    uint32 buf;
    glGenBuffers(1, (GLuint*)&buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return buf;
}

void RenderDevice::destroyBuffer(uint32 bufObj)
{
    if (bufObj == 0) return;
    glDeleteBuffers(1, &bufObj);
}

void RenderDevice::setVertexBuffer(uint32 buf)
{
    glBindBuffer(GL_ARRAY_BUFFER, buf);
}

void RenderDevice::setIndexBuffer(uint32 buf)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
}

void RenderDevice::setVertexLayout(uint32 index, uint32 stride, const void* pointer)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, pointer);
}

void RenderDevice::draw(PrimType type, uint32 first, uint32 count)
{
    glDrawArrays(type, first, count);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void RenderDevice::draw(PrimType type, uint32 count)
{
    glDrawElements(type, count, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

SK_END_NAMESPACE
