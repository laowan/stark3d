#include "utils/fileutils.h"

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
