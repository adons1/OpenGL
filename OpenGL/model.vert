#version 330 core

layout (location = 0000) in vec3 aPos;
layout (location = 0000) in vec3 aNormal;
layout (location = 0000) in vec2 aTex;
layout (location = 0000) in vec3 aColor;

out vec3 Normal;
out vec3 color;
out vec3 crntPos;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 camMatrix;


void main()
{
	crntPos = vec3(view * model * vec4(1.0f * aPos, 1.0f));

	gl_Position = camMatrix * vec4(crntPos , 1.0f);

	texCoord = aTex;

	color = aColor;

	Normal = vec3(model * vec4(aNormal, 1.0f));
}