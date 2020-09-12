#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinate;

out vec2 sTextureCoordinate;

uniform mat4 uProjection;

void main()
{
    sTextureCoordinate = textureCoordinate;
    gl_Position = uProjection * vec4(position, 0.0f, 1.0f);
}
