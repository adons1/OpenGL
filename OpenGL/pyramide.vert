#version 330 core


layout (location = 8) in vec3 aPos;

layout (location = 9) in vec3 aColor;

layout (location = 10) in vec2 aTex;



out vec3 color;

out vec2 texCoord;


uniform float scale;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 camMatrix;

void main()
{
	
	gl_Position = camMatrix *  view *  model * vec4(scale * aPos, 1.0);
	
	color = aColor;
	
	texCoord = aTex;
}