#version 330 core


layout (location = 8) in vec3 aPos;

layout (location = 9) in vec3 aColor;

layout (location = 10) in vec2 aTex;

layout (location = 11) in vec3 aNormal;

out vec3 color;

out vec2 texCoord;

out vec3 Normal;

out vec3 crntPos;

uniform float scale;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 camMatrix;

void main()
{
	crntPos = vec3(view * model * vec4(scale * aPos, 1.0f));

	gl_Position = camMatrix * vec4(crntPos, 1.0);
	
	color = aColor;
	
	texCoord = aTex;

	Normal = vec3(model * vec4(aNormal, 1.0f));
}