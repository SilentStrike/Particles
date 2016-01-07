
#include "Program.hpp"

Program::Program()
{
    linked = false;
    id = glCreateProgram();
    if(id == 0)
        throw std::runtime_error("glCreateProgram failed!");
}

Program::~Program()
{
    for(unsigned i = 0; i < shaders.size(); ++i)
        glDeleteShader(shaders[i]->id);
    glDeleteProgram(id);
}

void Program::Add(Shader* shader)
{
    shaders.push_back(shader);
}

void Program::Compile()
{
    for(unsigned i = 0; i < shaders.size(); ++i)
    {
        if (!shaders[i]->IsLoaded())
            shaders[i]->Compile();
    }
}

void Program::Link()
{
    // attach shaders
    for(unsigned i = 0; i < shaders.size(); ++i)
        glAttachShader(id, shaders[i]->id);
    
    // link
    glLinkProgram(id);
    
    // detach shaders
    for(unsigned i = 0; i < shaders.size(); ++i)
        glDetachShader(id, shaders[i]->id);
    
    // check status
    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string msg("Program linking failure: ");
        GLint infoLogLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(id, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        glDeleteProgram(id); id = 0;
        throw std::runtime_error(msg);
    }
    linked = true;
}

void Program::Use()
{
    if (linked)
        glUseProgram(id);
}

GLint Program::GetAttribLocation(const GLchar* attribName) const
{
    if(!attribName)
        throw std::runtime_error("attribName was NULL");
    
    GLint attrib = glGetAttribLocation(id, attribName);
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    
    return attrib;
}

GLint Program::GetUniformLocation(const GLchar* uniformName) const
{
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");
    
    GLint uniform = glGetUniformLocation(id, uniformName);
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
    
    return uniform;
}

void Program::SetUniformValue(const char* name, const uint32_t val)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform1i(i, val);
}

void Program::SetUniformValue(const char* name, const uint32_t *val, uint32_t count)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform1iv(i, count, (const GLint *)val);
}

void Program::SetUniformValue(const char* name, const float val)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform1f(i, val);
}

void Program::SetUniformValue(const char* name, const float *val, uint32_t count)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform1fv(i, count, (const GLfloat *)&val[0]);
}

void Program::SetUniformValue(const char* name, const glm::vec2 &val)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform2fv(i, 1, glm::value_ptr(val));
}

void Program::SetUniformValue(const char* name, const glm::vec2 *val, uint32_t count)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform2fv(i, count, glm::value_ptr(val[0]));
}

void Program::SetUniformValue(const char* name, const glm::vec3 &val)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform3fv(i, 1, glm::value_ptr(val));
}

void Program::SetUniformValue(const char* name, const glm::vec3 *val, uint32_t count)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform3fv(i, count, glm::value_ptr(val[0]));
}

void Program::SetUniformValue(const char* name, const glm::vec4 &val)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform4f(i, val.x, val.y, val.z, val.w);
}

void Program::SetUniformValue(const char* name, const glm::vec4 *val, uint32_t count)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniform4fv(i, count, glm::value_ptr(val[0]));
}

void Program::SetUniformValue(const char* name, const glm::mat4 &val, bool transpose)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniformMatrix4fv(i, 1, transpose, glm::value_ptr(val));
}

void Program::SetUniformValue(const char* name, const glm::mat4 *val, uint32_t count, bool transpose)
{
    GLint i = glGetUniformLocation(id, name);
    if (i != -1)
        glUniformMatrix4fv(i, count, transpose ? GL_TRUE : GL_FALSE, (const float *)val);
}