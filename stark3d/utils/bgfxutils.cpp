#include "bgfxutils.h"
#include "bx/file.h"
#include "stdlib.h"

static bx::FileReaderI* s_fileReader = NULL;
static bx::FileWriterI* s_fileWriter = NULL;

bx::AllocatorI* getDefaultAllocator()
{
    static bx::DefaultAllocator s_allocator;
    return &s_allocator;
}

extern bx::AllocatorI* getDefaultAllocator();
bx::AllocatorI* g_allocator = getDefaultAllocator();

typedef bx::StringT<&g_allocator> String;

static String s_currentDir;

class FileReader : public bx::FileReader
{
    typedef bx::FileReader super;

public:
    virtual bool open(const bx::FilePath& _filePath, bx::Error* _err) override
    {
        String filePath(s_currentDir);
        filePath.append(_filePath.get());
        return super::open(filePath.getPtr(), _err);
    }
};

class FileWriter : public bx::FileWriter
{
    typedef bx::FileWriter super;

public:
    virtual bool open(const bx::FilePath& _filePath, bool _append, bx::Error* _err) override
    {
        String filePath(s_currentDir);
        filePath.append(_filePath.get());
        return super::open(filePath.getPtr(), _append, _err);
    }
};

static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
{
    if (bx::open(_reader, _filePath))
    {
        uint32_t size = (uint32_t)bx::getSize(_reader);
        const bgfx::Memory* mem = bgfx::alloc(size + 1);
        bx::read(_reader, mem->data, size);
        bx::close(_reader);
        mem->data[mem->size - 1] = '\0';
        return mem;
    }

    //DBG("Failed to load %s.", _filePath);
    return NULL;
}

static bgfx::ShaderHandle loadShader(const char* _name)
{
    char filePath[512];
    const char* shaderPath = "../res/shader/";
    bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath);
    bx::strCat(filePath, BX_COUNTOF(filePath), _name);
    bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

    bgfx::ShaderHandle handle = bgfx::createShader(loadMem(s_fileReader, filePath));
    bgfx::setName(handle, filePath);

    return handle;
}

bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName)
{
    if (!s_fileReader)
    {
        s_fileReader = BX_NEW(g_allocator, FileReader);
    }

    if (!s_fileWriter)
    {
        s_fileWriter = BX_NEW(g_allocator, FileWriter);
    }

    bgfx::ShaderHandle vsh = loadShader(_vsName);
    bgfx::ShaderHandle fsh = loadShader(_fsName);

    bgfx::ProgramHandle handle = bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
    return handle;
}