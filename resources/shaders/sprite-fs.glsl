#version 330 core

in vec2 sTextureCoordinate;
in float sTextureId;
in vec4 sColor;

out vec4 color;

uniform sampler2D uTextures[32];

void main()
{
    vec4 textureColor = sColor;

    // Textured sprite
    if (sTextureId > 0.0f) {
        int textureId = int(sTextureId - 0.5);
        textureColor = texture(uTextures[textureId], sTextureCoordinate);
    }

    color = textureColor;
}
