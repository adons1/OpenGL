#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float scale;
uniform float rotate;

void main()
{
	float new_X = aPos.x * cos(rotate) + aPos.y * -sin(rotate);
	float new_Y = aPos.x * sin(rotate) + aPos.y * cos(rotate);

	float circleX = 0.4f * cos(rotate / 10.0f);
	float circleY = 0.4f * sin(rotate / 10.0f);

	gl_Position = vec4(new_X * scale + circleX, new_Y * scale + circleY, aPos.z * scale, 1.0);
};