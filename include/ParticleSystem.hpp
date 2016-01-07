
#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include "ParticleData.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleGenerator.hpp"
#include "ParticleUpdater.hpp"
#include "ParticleRenderer.hpp"

class ParticleSystem
{
private:
    ParticleData particles;
    std::vector<std::shared_ptr<ParticleEmitter>> emitters;
    std::vector<std::shared_ptr<ParticleGenerator>> generators;
    std::vector<std::shared_ptr<ParticleUpdater>> updaters;
    std::vector<std::shared_ptr<ParticleRenderer>> renderers;
    
public:
    ParticleSystem(size_t max);
    
    void Update(float dt);
    void Shutdown();
    void Reset();
    
    void AddEmitter(std::shared_ptr<ParticleEmitter> e){emitters.push_back(e);}
    void AddGenerator(std::shared_ptr<ParticleGenerator> g){generators.push_back(g);}
    void AddUpdater(std::shared_ptr<ParticleUpdater> u){updaters.push_back(u);}
    void AddRenderer(std::shared_ptr<ParticleRenderer> r){renderers.push_back(r); r->Init(this);}
    
    size_t Count() const { return particles.count; }
    size_t AliveCount() const { return particles.count_alive; }
    ParticleData *Data() { return &particles; }
    Camera* GetCamera(){return renderers.front()->GetCamera();}
};

#endif