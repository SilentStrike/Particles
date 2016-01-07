
#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class Program
{
private:
    std::vector<Shader*> shaders;
    GLuint id;
    bool linked;
    
public:
    Program();
    ~Program();
    
    void Use();
    void Add(Shader *shader);
    void Compile();
    void Link();
    
    GLuint GetID(){ return id; }
    bool GetLinked(){ return linked; }
    
    GLint GetAttribLocation(const GLchar* attribName) const;
    GLint GetUniformLocation(const GLchar* uniformName) const;
    
    void SetUniformValue(const char* name, const uint32_t val);
    void SetUniformValue(const char* name, const uint32_t * val, uint32_t count);
    void SetUniformValue(const char* name, const float val);
    void SetUniformValue(const char* name, const float * val, uint32_t count);
    void SetUniformValue(const char* name, const glm::vec2 & val);
    void SetUniformValue(const char* name, const glm::vec2 * val, uint32_t count);
    void SetUniformValue(const char* name, const glm::vec3 & val);
    void SetUniformValue(const char* name, const glm::vec3 * val, uint32_t count);
    void SetUniformValue(const char* name, const glm::vec4 & val);
    void SetUniformValue(const char* name, const glm::vec4 * val, uint32_t count);
    void SetUniformValue(const char* name, const glm::mat4 & val, bool transpose = false);
    void SetUniformValue(const char* name, const glm::mat4 * val, uint32_t count, bool transpose = false);
};

#endif