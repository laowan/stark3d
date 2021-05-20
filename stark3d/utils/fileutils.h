#pragma once

#include "global.h"
#include "utils/data.h"
#include <string>

SK_BEGIN_NAMESPACE

class ResizableBuffer
{
public:
    virtual ~ResizableBuffer()
    {
    }
    virtual void resize(size_t size) = 0;
    virtual void* buffer() const = 0;
};

template<typename T>
class ResizableBufferAdapter
{
};

template<>
class ResizableBufferAdapter<Data> : public ResizableBuffer {
    typedef Data BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer)
    {}

    virtual void resize(size_t size)
    {
        if (static_cast<size_t>(_buffer->getSize()) < size)
        {
            auto old = _buffer->getBytes();
            void* buffer = ::realloc(old, size);
            if (buffer)
                _buffer->fastSet((unsigned char*)buffer, size);
        }
    }

    virtual void* buffer() const
    {
        return _buffer->getBytes();
    }
};

void PathJoin(std::string& dst, const std::string& base, const std::string& name);
bool GetParentPath(const std::string& strBasePath, std::string& parentPath);
Data GetDataFromFile(const std::string& filename);
std::string GetTextFromFile(const std::string& filename);

SK_END_NAMESPACE

