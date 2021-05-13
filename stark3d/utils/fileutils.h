#pragma once

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

void PathJoin(std::string& dst, const std::string& base, const std::string& name);
bool GetParentPath(const std::string& strBasePath, std::string& parentPath);

SK_END_NAMESPACE

