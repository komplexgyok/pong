#version 330 core

in vec2 sTextureCoordinates;
in float sTextureId;
in vec4 sColor;
in float sIsText;

out vec4 color;

uniform sampler2D uTextures[32];

void main()
{
    vec4 textureColor = sColor;

    // Textured sprite
    if (sTextureId > 0.0f) {
        int textureId = int(sTextureId - 0.5f);
        textureColor = texture(uTextures[textureId], sTextureCoordinates);
    }

    if (sIsText > 0.0f) {
        color = vec4(1.0f, 1.0f, 1.0f, textureColor.r) * sColor;
    }
    else {
        color = textureColor;
    }
}
