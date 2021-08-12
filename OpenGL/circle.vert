#version 330 core
layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aaColor;

out vec3 color;
uniform vec3 move;
void main()
{
	gl_Position = vec4(aPos.x+move.x, aPos.y+move.y, aPos.z+move.z, 1.0);
	color = aaColor;
};