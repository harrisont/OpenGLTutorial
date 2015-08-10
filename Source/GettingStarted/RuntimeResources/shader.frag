#version 330 core

in vec3 vertexColor;
in vec2 vertexTextureCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixValue;

void main()
{
    color =
        mix(
            texture(ourTexture1, vertexTextureCoord),
            texture(ourTexture2, vertexTextureCoord),
            mixValue)
        * vec4(vertexColor, 1);
}
