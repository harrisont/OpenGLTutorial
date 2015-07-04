#version 330 core

in vec3 vertexColor;
in vec2 vertexTextureCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, vertexTextureCoord);
}
