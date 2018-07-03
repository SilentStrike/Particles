
#include "ParticleUpdater.hpp"

void AttractorUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
    {
        glm::vec3 v;
        v.x = position.x - p->position[i].x;
        v.y = position.y - p->position[i].y;
        v.z = position.z - p->position[i].z;
        glm::vec3 u = glm::normalize(v);
        float ds = glm::dot(v,v);
        if(ds > 0.01)
            p->acceleration[i] += glm::vec4(u,0) * (mass / ds) * dt;
    }
}

void AccelerationUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
        p->acceleration[i] += dt * acceleration;
}

void VelocityUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
        p->velocity[i] += dt * p->acceleration[i];
}

void PositionUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
        p->position[i] += dt * p->velocity[i];
}

void ColorUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
        p->color[i] = glm::mix(p->start_color[i], p->end_color[i], p->lifetimer[i] / p->lifetime[i]);
}

void LifeTimeUpdater::Update(float dt, ParticleData *p)
{
    size_t end = p->count_alive;
    for (size_t i = 0; i < end; ++i)
    {
        // update lifetime and kill
        p->lifetimer[i] += dt;
        if (p->lifetimer[i] > p->lifetime[i])
        {
            p->Kill(i);
            end = p->count_alive < p->count ? p->count_alive : p->count;
        }
    }
}

void GravityUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
    {
        for(size_t j = i + 1; j < p->count_alive; ++j)
        {
            // calc gravity force on all other particles
            glm::vec3 v;
            v.x = p->position[i].x - p->position[j].x;
            v.y = p->position[i].y - p->position[j].y;
            v.z = p->position[i].z - p->position[j].z;
            glm::vec3 u = glm::normalize(v);
            float ds = glm::dot(v,v);
            if(ds > 0.01)
            {
                float force = p->mass[i] * p->mass[j] / ds;
                p->acceleration[i] += glm::vec4(-u,0) * force * dt;
                p->acceleration[j] += glm::vec4(u,0) * force * dt;
            }
        }
    }
}

void WallUpdater::Update(float dt, ParticleData *p)
{
    for (size_t i = 0; i < p->count_alive; ++i)
    {
        // calc point along ray and intersection point
        glm::vec4 n_vel = glm::normalize(p->velocity[i]);
        float t = (-1 * (glm::dot(p->position[i], normal))) / (glm::dot(n_vel, normal));
        glm::vec4 p_ = t * n_vel;
        float penfactor = t / p->velocity[i].length();
        
        // collision
        if(penfactor <= 1)
        {
            // calc reflection vector
            glm::vec4 r = p_ - 2 * glm::dot(p_, normal) * normal;
            
            // final position is intersection and reflection vector
            p->position[i] += p_ + r;
            
            // final velocity is length multiplied by unit reflection vector
            //p->velocity[i] = p->velocity[i].length() * glm::normalize(r);
        }
    }
}
