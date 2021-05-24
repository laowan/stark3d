#pragma once

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Texture
{
public:
    Texture();
    ~Texture();
    bool createFromFile(const std::string& path);
    uint32 textureId() { return _textureId; }
private:
    uint32 _textureId;
};

SK_END_NAMESPACE