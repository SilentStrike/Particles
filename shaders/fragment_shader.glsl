#version 330

in vec4 outColor;
out vec4 fragColor;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, gl_PointCoord) * outColor;
}