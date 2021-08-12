#version 330 core
layout (location = 3) in vec3 aPos;
layout (location = 4) in vec3 aColor;
layout (location = 5) in vec2 aTex;

out vec3 color;

out vec2 texCoord;

uniform float rotate;

void main()
{
	float new_X = aPos.x * cos(rotate) + aPos.y * sin(rotate);
	float new_Y = aPos.x * -sin(rotate) + aPos.y * cos(rotate);

	gl_Position = vec4(new_X, new_Y, aPos.z, 1.0);
	color = aColor;
	texCoord = aTex;
};