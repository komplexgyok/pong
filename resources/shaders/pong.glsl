#VertexShader
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}

#FragmentShader
#version 330 core

out vec4 outColor;

void main()
{
    outColor = vec4(1.0f, 0.6f, 0.2f, 1.0f);
}
