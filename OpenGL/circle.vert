#version 330 core
layout (location = 3) in vec3 aPos;
layout (location = 4) in vec3 aaColor;

out vec3 color;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aaColor;
};