#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "scene/sprite.h"

SK_BEGIN_NAMESPACE

class STARK_API Particle : public Sprite
{
public:
    Particle();

    glm::vec2 position();
    void setPosition(glm::vec2 pos);

    glm::vec2 velocity();
    void setVelocity(glm::vec2 vel);

    float life();
    void setLife(float l);

    glm::vec4 color();
    void setColor(glm::vec4 col);
    
    void draw(Shader* shader, Texture* texture);

private:
    SK_DECLARE_IMPL(Particle);
};

SK_END_NAMESPACE

#endif
