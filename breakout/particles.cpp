#include "particles.h"

ParticleGenerator::ParticleGenerator(SK::Shader *shader, SK::Texture *texture, unsigned amount)
    : _shader(shader), _texture(texture), _amount(amount)
{
    lastUsedParticle = 0;
    init();
}

ParticleGenerator::~ParticleGenerator()
{
    for (size_t i = 0; i < _particles.size(); i++)
    {
        delete _particles[i];
    }
    _particles.clear();
}

void ParticleGenerator::update(float dt, GameObject *object, unsigned int newParticles, glm::vec2 offset)
{
    for (unsigned int i = 0; i < newParticles; i++)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(_particles[unusedParticle], object, offset);
    }

    int cnt = 0;
    for (size_t i = 0; i < _particles.size(); i++)
    {
        SK::Particle *p = _particles[i];
        p->setLife(p->life() - dt);
        if (p->life() > 0.0f)
        {
            p->setPosition(p->position() - p->velocity()*dt);

            glm::vec4 col = p->color();
            col.a -= dt*2.5;
            p->setColor(col);

            cnt++;
        }
    }
    std::cout << cnt << std::endl;
}

void ParticleGenerator::draw()
{
    for (size_t i = 0; i < _particles.size(); i++)
    {
        if (_particles[i]->life() > 0.0f)
            _particles[i]->draw(_shader, _texture);
    }
}

void ParticleGenerator::init()
{
    for (unsigned int i = 0; i < _amount; i++)
    {
        _particles.push_back(new SK::Particle());
    }
}

unsigned int ParticleGenerator::firstUnusedParticle()
{
    for (unsigned int i = lastUsedParticle; i < _amount; i++)
    {
        if (_particles[i]->life() <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }

    for (unsigned int i = 0; i < lastUsedParticle; i++)
    {
        if (_particles[i]->life() <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }
    
    lastUsedParticle = 0;

    return 0;
}

void ParticleGenerator::respawnParticle(SK::Particle *particle, GameObject *object, glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rcolor = 0.5 + (rand() % 100) / 100.0f;
    particle->setPosition(object->position + random + offset);
    particle->setColor(glm::vec4(rcolor, rcolor, rcolor, 1.0f));
    particle->setLife(0.1f);
    particle->setVelocity(object->velocity);
}

