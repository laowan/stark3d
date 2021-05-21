#include "utils/log.h"

#define FMT_HEADER_ONLY
#include "fmtlog.h"

SK_BEGIN_NAMESPACE

void _LogDebug(const char* tag, const char* format, ...)
{
    va_list vaList;
    va_start(vaList, format);
    fmt::print(format, vaList);
    va_end(vaList);
}

void _LogInfo(const char* tag, const char* format, ...)
{
    va_list vaList;
    va_start(vaList, format);
    fmt::print(format, vaList);
    //logi(format, vaList);
    va_end(vaList);
}

void _LogWarn(const char* tag, const char* format, ...)
{
    va_list vaList;
    va_start(vaList, format);
    fmt::print(format, vaList);
    va_end(vaList);
}

void _LogError(const char* tag, const char* format, ...)
{
    va_list vaList;
    va_start(vaList, format);
    fmt::print(format, vaList);
    va_end(vaList);
}

SK_END_NAMESPACE