#ifndef _RENDERDEVICE_H
#define _RENDERDEVICE_H

#include "global.h"
#include <glload/gl_3_3_comp.h>

#include <vector>

SK_BEGIN_NAMESPACE

enum PrimType
{
    PRIM_TRIANGLES = GL_TRIANGLES,
    PRIM_TRIANGLE_STRIP = GL_TRIANGLE_STRIP
};

template<class T>
class ObjectPool
{
public:
    uint32 add(const T &obj)
    {
        if (!_freeList.empty())
        {
            uint32 index = _freeList.back();
            _freeList.pop_back();
            _objects[index] = obj;
            return index + 1;
        }
        else
        {
            _objects.push_back(obj);
            return (uint32)_objects.size();
        }
    }

    void remove(uint32 handle)
    {
        ASSERT(handle > 0 && handle <= _objects.size());

        _objects[handle - 1] = T();  // Destruct and replace with default object
        _freeList.push_back(handle - 1);
    }

    T &getRef(uint32 handle)
    {
        ASSERT(handle > 0 && handle <= _objects.size());

        return _objects[handle - 1];
    }

    friend class RenderDevice;

private:
    std::vector<T>       _objects;
    std::vector<uint32>  _freeList;
};

class RenderBuffer
{
public:
    uint32 fbo;
    uint32 depthTexture, colorTexture;
};

class STARK_API RenderDevice
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
    void draw(PrimType type, uint32 count);

    uint32 createRenderBuffer(uint32 width, uint32 height);
    void destroyRenderBuffer(uint32 obj);
    void setRenderBuffer(uint32 obj);
    uint32 getRenderBufferTexture(uint32 obj);

private:
    SK_DECLARE_IMPL(RenderDevice);
};

SK_END_NAMESPACE

#endif