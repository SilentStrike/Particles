
#include "ParticleGenerator.hpp"

TextureGenerator::TextureGenerator(std::string filename)
{
    AddTexture(filename);
}

void TextureGenerator::Generate(float dt, ParticleData *p, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
        p->textures[i] = textures[rand() % textures.size()].get()->Get();
}

void TextureGenerator::AddTexture(std::string filename)
{
    textures.push_back(std::make_shared<Texture>(filename.c_str()));
}

void VelocityGenerator::Generate(float dt, ParticleData *p, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        p->velocity[i] = glm::vec4(((float) rand() / RAND_MAX) * 2 - 1,
                                   ((float) rand() / RAND_MAX) * 2 - 1,
                                   ((float) rand() / RAND_MAX) * 2 - 1,
                                   0);
        p->velocity[i] = glm::normalize(p->velocity[i]);
        p->velocity[i] *= min_vel + (((float) rand()) / RAND_MAX) * (max_vel - min_vel);
    }
}

void ColorGenerator::Generate(float dt, ParticleData *p, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        p->start_color[i] = start_color;
        p->end_color[i] = end_color;
    }
}

void LifetimeGenerator::Generate(float dt, ParticleData *p, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        p->lifetime[i] = min_life + (((float) rand()) / RAND_MAX) * (max_life - min_life);
        p->lifetimer[i] = 0;
    }
}

void MassGenerator::Generate(float dt, ParticleData *p, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
        p->mass[i] = min_mass + (((float) rand()) / RAND_MAX) * (max_mass - min_mass);
}