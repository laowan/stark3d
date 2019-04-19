#ifndef SK_RESOURCES_H
#define SK_RESOURCES_H

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Resources
{
public:
    static void LoadGltf(const std::string& filepath);
};

SK_END_NAMESPACE
#endif SK_RESOURCES_H
