
#include "ParticleEmitter.hpp"

void PointEmitter::Emit(float dt, ParticleData *p)
{
    accumulator += dt;
    size_t n = accumulator * emit_rate;
    accumulator = fmodf(accumulator, 1 / emit_rate);
    const size_t start = p->count_alive;
    const size_t end = std::min(start + n, p->count - 1);
    for (size_t i = start; i < end; ++i)
    {
        p->Wake(i);
        p->position[i] = glm::vec4(0,0,0,1);
    }
}

void LineEmitter::Emit(float dt, ParticleData *p)
{
    const size_t n = static_cast<size_t>(dt * emit_rate);
    const size_t start = p->count_alive;
    const size_t end = std::min(start + n, p->count - 1);
    for (size_t i = start; i < end; ++i)
    {
        p->Wake(i);
        p->position[i] = glm::mix(a, b, (float) rand() / RAND_MAX);
    }
}

void SphereEmitter::Emit(float dt, ParticleData *p)
{
    const size_t n = static_cast<size_t>(dt * emit_rate);
    const size_t start = p->count_alive;
    const size_t end = std::min(start + n, p->count - 1);
    for (size_t i = start; i < end; ++i)
    {
        p->Wake(i);
        
        float theta = 2 * M_PI * ((float) rand() / RAND_MAX);
        float phi = acos(1 - 2 * ((float) rand() / RAND_MAX)); // inverse cdf for uniformity
        float x = radius * sin(phi) * cos(theta);
        float y = radius * sin(phi) * sin(theta);
        float z = radius * cos(phi);
        p->position[i] = position + glm::vec4(x,y,z,0);
    }
}

void SphereCloudEmitter::Emit(float dt, ParticleData *p)
{
    const size_t n = static_cast<size_t>(dt * emit_rate);
    const size_t start = p->count_alive;
    const size_t end = std::min(start + n, p->count - 1);
    for (size_t i = start; i < end; ++i)
    {
        p->Wake(i);
        float theta = 2 * M_PI * ((float) rand() / RAND_MAX);
        float phi = acos(1 - 2 * ((float) rand() / RAND_MAX)); // inverse cdf for uniformity
        float r = (float) rand() / RAND_MAX * radius;
        r = sqrt(r);
        float x = r * sin(phi) * cos(theta);
        float y = r * sin(phi) * sin(theta);
        float z = r * cos(phi);
        p->position[i] = position + glm::vec4(x,y,z,0);
    }
}

void BoxCloudEmitter::Emit(float dt, ParticleData *p)
{
    const size_t n = static_cast<size_t>(dt * emit_rate);
    const size_t start = p->count_alive;
    const size_t end = std::min(start + n, p->count - 1);
    for (size_t i = start; i < end; ++i)
    {
        p->Wake(i);
        float x = min.x + ((float) rand() / RAND_MAX) * (max.x - min.x);
        float y = min.y + ((float) rand() / RAND_MAX) * (max.y - min.y);
        float z = min.z + ((float) rand() / RAND_MAX) * (max.z - min.z);
        p->position[i] = glm::vec4(x,y,z,1);
    }
}