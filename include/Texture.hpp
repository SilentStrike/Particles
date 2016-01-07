
#include <iostream>
#include <GL/glew.h>
#include "SOIL/SOIL.h"

class Texture
{
private:
    int width;
    int height;
    GLuint texture;
    
public:
    Texture(std::string filename);
    ~Texture();
    
    void Bind();
    GLuint Get(){return texture;}
};