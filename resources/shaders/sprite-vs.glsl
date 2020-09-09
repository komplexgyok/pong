#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 uModel;
uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * uModel * vec4(position, 0.0f, 1.0f);
}
