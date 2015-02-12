#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "node.h"

SK_BEGIN_NAMESPACE

class Texture : public SceneNode
{
public:
    Texture(int minMagFiler = GL_LINEAR, int wrapMode = GL_CLAMP_TO_EDGE);
    ~Texture();

    bool render(RenderAction* act);

private:
    uint32 _object;
};

SK_END_NAMESPACE

#endif
