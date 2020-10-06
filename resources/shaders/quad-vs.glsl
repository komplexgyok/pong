#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in float textureId;
layout (location = 3) in vec4 color;
layout (location = 4) in float isText;

out vec2 sTextureCoordinates;
out float sTextureId;
out vec4 sColor;
out float sIsText;

uniform mat4 uModel = mat4(1.0);
uniform mat4 uView = mat4(1.0);
uniform mat4 uProjection;

void main()
{
    sTextureCoordinates = textureCoordinates;
    sTextureId = textureId;
    sColor = color;
    sIsText = isText;
    gl_Position = uProjection * uView * uModel * vec4(position, 0.0f, 1.0f);
}
