#pragma once

#include "global.h"

SK_BEGIN_NAMESPACE

void _LogDebug(const char* tag, const char* format, ...);
void _LogInfo(const char* tag, const char* format, ...);
void _LogWarn(const char* tag, const char* format, ...);
void _LogError(const char* tag, const char* format, ...);

SK_END_NAMESPACE

#define SK_LOGD(...) SK::_LogDebug("SK", __VA_ARGS__)
#define SK_LOGI(...) SK::_LogInfo("SK", __VA_ARGS__) 
#define SK_LOGW(...) SK::_LogWarn("SK", __VA_ARGS__) 
#define SK_LOGE(...) SK::_LogError("SK", __VA_ARGS__)
