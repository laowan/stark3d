#include "renderdevice.h"

SK_BEGIN_NAMESPACE

class RenderDeviceImpl : public Impl<RenderDevice>
{
public:
    ObjectPool<RenderBuffer> _renderBuffers;
};

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

uint32 RenderDevice::createRenderBuffer(uint32 width, uint32 height)
{
    SK_D(RenderDevice);
    RenderBuffer rb;

    glGenFramebuffers(1, &rb.fbo);
    glGenTextures(1, &rb.colorTexture);
    glGenTextures(1, &rb.depthTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, rb.fbo);

    glBindTexture(GL_TEXTURE_2D, rb.colorTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colortexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rb.colorTexture, 0);

    glBindTexture(GL_TEXTURE_2D, rb.depthTexture);
    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthtexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rb.depthTexture, 0);


    static const GLenum draw_buffer[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return d->_renderBuffers.add(rb);
}

void RenderDevice::destroyRenderBuffer(uint32 obj)
{
    SK_D(RenderDevice);
    RenderBuffer& rb = d->_renderBuffers.getRef(obj);
    glDeleteFramebuffers(1, &rb.fbo);
    glDeleteTextures(1, &rb.colorTexture);
    glDeleteTextures(1, &rb.depthTexture);

    d->_renderBuffers.remove(obj);
}

void RenderDevice::setRenderBuffer(uint32 obj)
{
    SK_D(RenderDevice);
    if (obj == 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else
    {
        RenderBuffer& rb = d->_renderBuffers.getRef(obj);
        glBindFramebuffer(GL_FRAMEBUFFER, rb.fbo);
    }
}

uint32 RenderDevice::getRenderBufferTexture(uint32 obj)
{
    SK_D(RenderDevice);
    RenderBuffer& rb = d->_renderBuffers.getRef(obj);
    return rb.colorTexture;
}

SK_END_NAMESPACE
