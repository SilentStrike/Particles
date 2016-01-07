
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ParticleSystem.hpp"

void OnError(int errorCode, const char* msg)
{
    throw std::runtime_error(msg);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void AppMain()
{
    // initialise GLFW
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // windowed fullscreen
    GLFWwindow *window;
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    window = glfwCreateWindow(mode->width, mode->height, "Particles", monitor, NULL);
    if(!window)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
    // hide the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    // GLFW settings
    glfwMakeContextCurrent(window);
    
    // initialise GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // input
    glfwSetKeyCallback(window, key_callback);
    
    // initialize particle system
    ParticleSystem *ps = new ParticleSystem(10000);
    
    // emitters
    ps->AddEmitter(std::make_shared<SphereCloudEmitter>(glm::vec3(0,0,0), 1));
    
    // generators
    std::shared_ptr<TextureGenerator> tg = std::make_shared<TextureGenerator>();
    tg->AddTexture("resources/textures/fuzzball.png");
    ps->AddGenerator(tg);
    ps->AddGenerator(std::make_shared<VelocityGenerator>(0.1,1));
    ps->AddGenerator(std::make_shared<ColorGenerator>(glm::vec4(1,1,1,1), glm::vec4(0.5,0.5,1,0)));
    ps->AddGenerator(std::make_shared<LifetimeGenerator>(1));
    ps->AddGenerator(std::make_shared<MassGenerator>(1));
    
    // updaters
    ps->AddUpdater(std::make_shared<VelocityUpdater>());
    ps->AddUpdater(std::make_shared<PositionUpdater>());
    ps->AddUpdater(std::make_shared<ColorUpdater>());
    ps->AddUpdater(std::make_shared<LifeTimeUpdater>());
    
    // renderer
    ps->AddRenderer(std::make_shared<OpenGLRenderer>());
    
    // run while the window is open
    while(!glfwWindowShouldClose(window))
    {
        // process pending events
        glfwPollEvents();
        
        // rotation
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) ps->GetCamera()->Rotate(-1, 0);
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) ps->GetCamera()->Rotate(1, 0);
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) ps->GetCamera()->Rotate(0, -1);
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) ps->GetCamera()->Rotate(0, 1);
        
        // translation
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->up());
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->down());
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->left());
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->right());
        if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->forward());
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) ps->GetCamera()->Move(ps->GetCamera()->backward());

        // clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // update system
        ps->Update(0.01);
        
        // draw
        glfwSwapBuffers(window);
        
        // process pending events
        glfwPollEvents();
        
        // hack
        usleep(10000);
    }
    
    // clean up and exit
    glfwTerminate();
}

int main(int argc, char *argv[])
{
    srand((unsigned int)time(nullptr));
    try {
        AppMain();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
