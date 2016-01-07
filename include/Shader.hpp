
#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

class Shader
{
friend class Program;
private:
    GLuint id;
    GLuint type;
    std::string name;
    std::string path;
    bool loaded;
    
    void Compile();
    
public:
    Shader(std::string path, GLuint type);
    ~Shader();
    
    GLuint GetID(){ return id; }
    std::string GetName(){ return name; }
    std::string GetPath(){ return path; }
    GLuint GetType(){ return type; }
    bool IsLoaded(){ return loaded; }
};

#endif