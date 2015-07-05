#version 330 core

in vec3 vertexColor;
in vec2 vertexTextureCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    //color = texture(ourTexture1, vertexTextureCoord) * vec4(vertexColor, 1);
    color = mix(texture(ourTexture1, vertexTextureCoord), texture(ourTexture2, vertexTextureCoord), 0.2);
}
