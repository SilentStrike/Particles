
#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(size_t max)
{
    particles.Generate(max);
}

void ParticleSystem::Update(float dt)
{
    // reset acceleration
    for (size_t i = 0; i < particles.count_alive; ++i)
        particles.acceleration[i] = glm::vec4(0.0f);
    
    // emit
    size_t before = particles.count_alive;
    for(auto iter = emitters.begin(); iter != emitters.end(); ++iter)
        (*iter)->Emit(dt, &particles);
    size_t after = particles.count_alive;
    
    // generate
    for(auto iter = generators.begin(); iter != generators.end(); ++iter)
        (*iter)->Generate(dt, &particles, before, after);
    
    // update
    for(auto iter = updaters.begin(); iter != updaters.end(); ++iter)
        (*iter)->Update(dt, &particles);
    
    // render
    for(auto iter = renderers.begin(); iter != renderers.end(); ++iter)
    {
        (*iter)->Update();
        (*iter)->Render();
    }
}

void ParticleSystem::Reset()
{
    particles.count_alive = 0;
}