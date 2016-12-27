#include "scene/particle.h"

SK_BEGIN_NAMESPACE

class ParticleImpl : public Impl<Particle>
{
public:
    glm::vec2 _position, _velocity;
    glm::vec4 _color;
    float _life;
};

Particle::Particle()
{
    SK_I(Particle);
    d->_position = glm::vec2(0.0f);
    d->_velocity = glm::vec2(0.0f);
    d->_color = glm::vec4(1.0f); 
    d->_life = 0.0f;
}

glm::vec2 Particle::position()
{
    SK_D(Particle);
    return d->_position; 
}

void Particle::setPosition(glm::vec2 pos)
{
    SK_D(Particle);
    d->_position = pos;
}

glm::vec2 Particle::velocity() 
{
    SK_D(Particle);
    return d->_velocity;
}

void Particle::setVelocity(glm::vec2 vel)
{
    SK_D(Particle);
    d->_velocity = vel; 
}

float Particle::life()
{
    SK_D(Particle);
    return d->_life; 
}

void Particle::setLife(float l)
{ 
    SK_D(Particle);
    d->_life = l; 
}

glm::vec4 Particle::color() 
{
    SK_D(Particle);
    return d->_color; 
}

void Particle::setColor(glm::vec4 col) 
{ 
    SK_D(Particle);
    d->_color = col;
}

void Particle::draw(Shader* shader, Texture* texture)
{
    SK_D(Particle);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    Sprite::draw(shader, texture, d->_position);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

SK_END_NAMESPACE