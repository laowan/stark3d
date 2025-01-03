#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "global.h"
#include "utils/gldefine.h"

#include <string>

SK_BEGIN_NAMESPACE

class Texture
{
public:
    Texture(int minMagFiler = GL_LINEAR, int wrapMode = GL_CLAMP_TO_EDGE);
    Texture(std::string file, int minMagFiler = GL_LINEAR, int wrapMode = GL_CLAMP_TO_EDGE);
    ~Texture();

    void bind();

private:
    void init(std::string file, int minMagFiler, int wrapMode);
    uint32 _object;
};

SK_END_NAMESPACE

#endif
