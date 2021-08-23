#version 330 core

layout (location = 12) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

uniform float scale;

void main()
{
	gl_Position = camMatrix * model * vec4(aPos * scale, 1.0f);
}