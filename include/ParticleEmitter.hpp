
#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "ParticleData.hpp"

class ParticleEmitter
{
protected:
    float emit_rate;
    float accumulator;

public:
    ParticleEmitter() : emit_rate(100000), accumulator(0) {}
    virtual void Emit(float dt, ParticleData *p) = 0;
};

class PointEmitter : public ParticleEmitter
{
private:
    glm::vec4 position;

public:
    PointEmitter(glm::vec3 pos) : position(pos,1) {}
    void Emit(float dt, ParticleData *p);
};

class LineEmitter : public ParticleEmitter
{
private:
    glm::vec4 a;
    glm::vec4 b;

public:
    LineEmitter(glm::vec3 p1, glm::vec3 p2) : a(p1,1), b(p2,1) {}
    void Emit(float dt, ParticleData *p);
};

class SphereEmitter : public ParticleEmitter
{
private:
    glm::vec4 position;
    float radius;

public:
    SphereEmitter(glm::vec3 p, float r) : position(p,1), radius(r) {}
    void Emit(float dt, ParticleData *p);
};

class SphereCloudEmitter : public ParticleEmitter
{
private:
    glm::vec4 position;
    float radius;

public:
    SphereCloudEmitter(glm::vec3 p, float r) : position(p,1), radius(r) {}
    void Emit(float dt, ParticleData *p);
};

class BoxCloudEmitter : public ParticleEmitter
{
private:
    glm::vec4 min;
    glm::vec4 max;

public:
    BoxCloudEmitter(glm::vec3 min_p, glm::vec3 max_p) : min(min_p,1), max(max_p,1) {}
    void Emit(float dt, ParticleData *p);
};

#endif
