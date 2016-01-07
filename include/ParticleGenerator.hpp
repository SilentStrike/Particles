
#ifndef PARTICLEGENERATOR_HPP
#define PARTICLEGENERATOR_HPP

#include <vector>
#include "ParticleData.hpp"
#include "Texture.hpp"

class ParticleGenerator
{
public:
    virtual void Generate(float dt, ParticleData *p, size_t start, size_t end) = 0;
};

class TextureGenerator : public ParticleGenerator
{
private:
    std::vector<std::shared_ptr<Texture>> textures;
    
public:
    TextureGenerator() {}
    TextureGenerator(std::string filename);
    void AddTexture(std::string filename);
    void Generate(float dt, ParticleData *p, size_t start, size_t end);
};

class VelocityGenerator : public ParticleGenerator
{
private:
    float min_vel;
    float max_vel;
    
public:
    VelocityGenerator(float vel) : min_vel(vel), max_vel(vel) {}
    VelocityGenerator(float min, float max) : min_vel(min), max_vel(max) {}
    void Generate(float dt, ParticleData *p, size_t start, size_t end);
};

class ColorGenerator : public ParticleGenerator
{
private:
    glm::vec4 start_color;
    glm::vec4 end_color;
    
public:
    ColorGenerator(glm::vec4 color) : start_color(color), end_color(color) {}
    ColorGenerator(glm::vec4 start, glm::vec4 end) : start_color(start), end_color(end) {}
    void Generate(float dt, ParticleData *p, size_t start, size_t end);
};

class LifetimeGenerator : public ParticleGenerator
{
private:
    float min_life;
    float max_life;
    
public:
    LifetimeGenerator(float t) : min_life(t), max_life(t) {}
    LifetimeGenerator(float min, float max) : min_life(min), max_life(max) {}
    void Generate(float dt, ParticleData *p, size_t start, size_t end);
};

class MassGenerator : public ParticleGenerator
{
private:
    float min_mass;
    float max_mass;
    
public:
    MassGenerator(float m) : min_mass(m), max_mass(m) {}
    MassGenerator(float min, float max) : min_mass(min), max_mass(max) {}
    void Generate(float dt, ParticleData *p, size_t start, size_t end);
};

#endif