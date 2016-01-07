
#include "Shader.hpp"

Shader::Shader(std::string path, GLuint type)
{
    this->path = path;
    this->type = type;
    this->name = path.substr(path.find_last_of("/\\") + 1);
    loaded = false;
    Compile();
}

Shader::~Shader()
{
    glDeleteShader(id);
}

void Shader::Compile()
{
    // open shader file
    std::ifstream f;
    f.open(path.c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open())
        throw std::runtime_error(std::string("Failed to open file: ") + path);
    
    // create shader program
    id = glCreateShader(type);
    if(id == 0)
        throw std::runtime_error("glCreateShader failed!");
    
    // set the source code
    std::string text, line;
    while(std::getline(f, line))
        text += line + "\n";
    const char* code = text.c_str();
    glShaderSource(id, 1, (const GLchar**)&code, NULL);
    
    // compile
    glCompileShader(id);
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string msg("Compile failure in shader:\n");
        GLint infoLogLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        glDeleteShader(id); id = 0;
        throw std::runtime_error(msg);
    }
    loaded = true;
}

