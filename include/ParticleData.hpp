
#ifndef PARTICLEDATA_HPP
#define PARTICLEDATA_HPP

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ParticleData
{
public:
    size_t count;          // total particles
    size_t count_alive;    // alive particles
    
    // attributes
    std::unique_ptr<unsigned int[]> textures;
    std::unique_ptr<glm::vec4[]> position;
    std::unique_ptr<glm::vec4[]> velocity;
    std::unique_ptr<glm::vec4[]> acceleration;
    std::unique_ptr<glm::vec4[]> color;
    std::unique_ptr<glm::vec4[]> start_color;
    std::unique_ptr<glm::vec4[]> end_color;
    std::unique_ptr<float[]> lifetimer;
    std::unique_ptr<float[]> lifetime;
    std::unique_ptr<float[]> mass;
    
    ParticleData() {}
    explicit ParticleData(size_t max) { Generate(max); }
    ~ParticleData() {}
    
    ParticleData(const ParticleData &) = delete;
    ParticleData &operator=(const ParticleData &) = delete;
    
    void Generate(size_t max);
    void Kill(size_t index);
    void Wake(size_t index);
    void SwapData(size_t a, size_t b);
};

#endif