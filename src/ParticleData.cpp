
#include "ParticleData.hpp"

void ParticleData::Generate(size_t max)
{
    count = max;
    count_alive = 0;
    textures.reset(new unsigned int[max]);
    position.reset(new glm::vec4[max]);
    velocity.reset(new glm::vec4[max]);
    acceleration.reset(new glm::vec4[max]);
    color.reset(new glm::vec4[max]);
    start_color.reset(new glm::vec4[max]);
    end_color.reset(new glm::vec4[max]);
    lifetimer.reset(new float[max]);
    lifetime.reset(new float[max]);
    mass.reset(new float[max]);
}

void ParticleData::Kill(size_t index)
{
    if (count_alive > 0)
    {
        SwapData(index, count_alive - 1);
        count_alive--;
    }
}

void ParticleData::Wake(size_t index)
{
    if (count_alive < count)
    {
        SwapData(index, count_alive);
        count_alive++;
    }
}

void ParticleData::SwapData(size_t a, size_t b)
{
    std::swap(textures[a], textures[b]);
    std::swap(position[a], position[b]);
    std::swap(velocity[a], velocity[b]);
    std::swap(acceleration[a], acceleration[b]);
    std::swap(color[a], color[b]);
    std::swap(start_color[a], start_color[b]);
    std::swap(end_color[a], end_color[b]);
    std::swap(lifetimer[a], lifetimer[b]);
    std::swap(mass[a], mass[b]);
}
