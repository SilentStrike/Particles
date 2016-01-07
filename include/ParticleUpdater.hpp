
#ifndef PARTICLEUPDATER_HPP
#define PARTICLEUPDATER_HPP

#include "ParticleData.hpp"

class ParticleUpdater
{
public:
    virtual void Update(float dt, ParticleData *p) = 0;
};

class AttractorUpdater : public ParticleUpdater
{
private:
    glm::vec4 position;
    float mass;
    
public:
    AttractorUpdater(glm::vec3 p, float m = 1.0) : position(p,1), mass(m) {}
    void Update(float dt, ParticleData *p);
};

class AccelerationUpdater : public ParticleUpdater
{
private:
    glm::vec4 acceleration;
public:
    AccelerationUpdater(glm::vec3 a) : acceleration(a,0) {}
    void Update(float dt, ParticleData *p);
};

class VelocityUpdater : public ParticleUpdater
{
public:
    void Update(float dt, ParticleData *p);
};

class PositionUpdater : public ParticleUpdater
{
public:
    void Update(float dt, ParticleData *p);
};

class ColorUpdater : public ParticleUpdater
{
public:
    void Update(float dt, ParticleData *p);
};

class LifeTimeUpdater : public ParticleUpdater
{
public:
    void Update(float dt, ParticleData *p);
};

class GravityUpdater : public ParticleUpdater
{
public:
    void Update(float dt, ParticleData *p);
};

class WallUpdater : public ParticleUpdater
{
private:
    glm::vec4 position;
    glm::vec4 normal;
    float bounce;
    
public:
    WallUpdater(glm::vec3 p, glm::vec3 n, float bounce_factor = 1) : position(p,1), normal(n,1), bounce(bounce_factor) {}
    void Update(float dt, ParticleData *p);
};

#endif