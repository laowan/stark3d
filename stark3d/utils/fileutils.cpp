#include "utils/fileutils.h"

SK_BEGIN_NAMESPACE

#if defined(_MSC_VER)
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int cp, unsigned long flags, const char *str, int cbmb, wchar_t *widestr, int cchwide);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int cp, unsigned long flags, const wchar_t *widestr, int cchwide, char *str, int cbmb, const char *defchar, int *used_default);
#endif

static FILE *sk_fopen(char const *filename, char const *mode)
{
    FILE *f;
#if defined(_MSC_VER)
    wchar_t wMode[64];
    wchar_t wFilename[1024];
    if (0 == MultiByteToWideChar(65001 /* UTF8 */, 0, filename, -1, wFilename, sizeof(wFilename)))
        return 0;

    if (0 == MultiByteToWideChar(65001 /* UTF8 */, 0, mode, -1, wMode, sizeof(wMode)))
        return 0;

#if _MSC_VER >= 1400
    if (0 != _wfopen_s(&f, wFilename, wMode))
        f = 0;
#else
    f = _wfopen(wFilename, wMode);
#endif

#elif defined(_MSC_VER) && _MSC_VER >= 1400
    if (0 != fopen_s(&f, filename, mode))
        f = 0;
#else
    f = fopen(filename, mode);
#endif
    return f;
}

void PathJoin(std::string& dst, const std::string& base, const std::string& name)
{
    const std::string& src = &dst == &name ? std::string(name) : name;
    dst = base;
    size_t len = strlen(dst.c_str());
    if (dst[len - 1] != '/' && dst[len - 1] != '\\')
    {
        dst += "/";
    }
    dst += src;
}

bool GetParentPath(const std::string& strBasePath, std::string& parentPath)
{
    if ('\\' == *(strBasePath.end() - 1) || '/' == *(strBasePath.end() - 1))
    {
        parentPath = strBasePath.substr(0, strBasePath.length() - 1);
    }

    std::string::size_type pos = strBasePath.find_last_of('\\');
    if (pos != std::wstring::npos)
    {
        parentPath = strBasePath.substr(0, pos + 1);
    }
    else
    {
        pos = strBasePath.find_last_of('/');
        if (pos == std::string::npos)
        {
            return false;
        }
        parentPath = strBasePath.substr(0, pos + 1);
    }

    return true;
}

bool GetContents(const std::string& fullPath, Data* buffer)
{
    ResizableBufferAdapter<Data> buf(buffer);

    if (fullPath.empty())
    {
        printf("file GetContents path error: %s", fullPath.c_str());
        return false;
    }

    FILE *file = sk_fopen(fullPath.c_str(), "rb");
    if (!file)
    {
        printf("file GetContents open failed: %s", fullPath.c_str());
        return false;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    //
    // don't read file content if it is empty.
    //
    if (size == 0)
    {
        printf("file GetContents size empty: %s", fullPath.c_str());
        fclose(file);
        return false;
    }

    buf.resize(size);
    if (buf.buffer() == NULL)
    {
        printf("buffer resize failed");
        fclose(file);
        return false;
    }

    size_t sizeRead = fread(buf.buffer(), 1, size, file);
    //
    // fixed android read folder,fopen can open it and the size is not 0
    //
    if (sizeRead == 0)
    {
        printf("file GetContents sizeRead empty: %s", fullPath.c_str());
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

Data GetDataFromFile(const std::string& filename)
{
    Data d;
    bool result = GetContents(filename, &d);
    if (!result)
    {
        Data emptyData;
        printf("Get File error, return empty data, file path: %s", filename.c_str());
        return emptyData;
    }
    return d;
}

std::string GetTextFromFile(const std::string& filename)
{
    std::string str;
    Data data = GetDataFromFile(filename);
    if (data.getSize() > 0)
    {
        str = std::string((const char*)data.getBytes(), (size_t)data.getSize());
    }
    return str;
}

SK_END_NAMESPACE