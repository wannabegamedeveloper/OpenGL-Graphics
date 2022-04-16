#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

out vec4 color;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(-aPos.x, -aPos.y, 1.0, 1.0);
	color = vec4(aColor, 1.0);

	texCoord = aTex;
}