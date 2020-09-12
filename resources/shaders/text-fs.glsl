#version 330 core

in vec2 sTextureCoordinate;

out vec4 color;

uniform sampler2D uText;
uniform vec4 uTextColor;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(uText, sTextureCoordinate).r);
    color = vec4(uTextColor) * sampled;
}
