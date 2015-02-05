#ifndef _RENDERDEVICE_H
#define _RENDERDEVICE_H

#include "global.h"
#include <glload/gl_3_3.h>

namespace Util
{
enum PrimType
{
    PRIM_TRIANGLES = GL_TRIANGLES,
    PRIM_TRIANGLE_STRIP = GL_TRIANGLE_STRIP
};

class RenderDevice
{
public:
    RenderDevice();
    ~RenderDevice();

    uint32 createVertexBuffer(uint32 size, const void* data);
    uint32 createIndexBuffer(uint32 size, const void* data);
    void destroyBuffer(uint32 bufObj);

    void setVertexBuffer(uint32 buf);
    void setIndexBuffer(uint32 buf);
    void setVertexLayout(uint32 index, uint32 stride, const void* pointer);
    void draw(PrimType type, uint32 first, uint32 count);
};

}

#endif