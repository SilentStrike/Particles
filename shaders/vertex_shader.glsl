#version 330

uniform mat4 modelview;
uniform mat4 projection;

in vec4 vertex;
in vec4 color;

out vec4 outColor;

void main()
{
    vec4 eyePos = modelview * vertex;
    gl_Position = projection * eyePos;
    
    outColor = color;
    
    float dist = length(eyePos.xyz);
    float att = inversesqrt(0.1 * dist);
    gl_PointSize = 3 * att;
}