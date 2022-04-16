#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform float scale;
uniform sampler2D tex0;

void main()
{
	FragColor = color;
}