#ifndef _EFFECT_H
#define _EFFECT_H

#include "global.h"

SK_BEGIN_NAMESPACE

class Effect
{
public:
    virtual void render() = 0; 
};

class EffectNormal : public Effect
{
public:
    void render();
};

class EffectTextureMap : public Effect
{
public:
    EffectTextureMap();
    ~EffectTextureMap();
    void render();
private:
    uint32 _vb;
};

SK_END_NAMESPACE

#endif
