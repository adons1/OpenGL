#version 330 core
layout (location = 2) in vec3 aPos;

uniform float rotate;

void main()
{
	float new_X = aPos.x * cos(rotate) + aPos.y * -sin(rotate);
	float new_Y = aPos.x * sin(rotate) + aPos.y * cos(rotate);

	gl_Position = vec4(new_X, new_Y, aPos.z, 1.0);
};