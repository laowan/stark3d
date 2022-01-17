#ifndef PARTICLES_H
#define PARTICLES_H

#include "base.h"
#include "gameobject.h"

class ParticleGenerator
{
public:
    ParticleGenerator(SK::Shader *shader, SK::Texture *texture, unsigned amount);
    ~ParticleGenerator();

    void update(float dt, GameObject *object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f,0.0f));
    void draw();

private:
    void init();
    unsigned int firstUnusedParticle();
    void respawnParticle(SK::Particle *particle, GameObject *object, glm::vec2 offset = glm::vec2(0.0f));

private:
    std::vector<SK::Particle*> _particles;
    unsigned int _amount;
    SK::Shader *_shader;
    SK::Texture *_texture;
    unsigned int lastUsedParticle;
};

#endif
