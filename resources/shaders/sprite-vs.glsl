#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinate;
layout (location = 2) in float textureId;
layout (location = 3) in vec4 color;

out vec2 sTextureCoordinate;
out float sTextureId;
out vec4 sColor;

uniform mat4 uProjection;

void main()
{
    sTextureCoordinate = textureCoordinate;
    sTextureId = textureId;
    sColor = color;
    gl_Position = uProjection * vec4(position, 0.0f, 1.0f);
}
