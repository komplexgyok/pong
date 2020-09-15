#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;

out vec4 sColor;

uniform mat4 uProjection;

void main()
{
    sColor = color;
    gl_Position = uProjection * vec4(position, 0.0f, 1.0f);
}
