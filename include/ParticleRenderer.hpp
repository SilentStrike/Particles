
#ifndef PARTICLERENDERER_HPP
#define PARTICLERENDERER_HPP

#include "Camera.hpp"
#include "Program.hpp"
#include "ParticleData.hpp"

class ParticleSystem;

class ParticleRenderer
{
protected:
    Camera *camera;
    ParticleSystem *system;
    
public:
    virtual void Init(ParticleSystem *s) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;
    
    Camera* GetCamera(){return camera;}
};

class OpenGLRenderer : public ParticleRenderer
{
private:
    GLuint vao;
    GLuint position_buf;
    GLuint color_buf;
    Program *shader;
    
public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    
    void Init(ParticleSystem *s);
    void Update();
    void Render();
    void Shutdown();
};

#endif