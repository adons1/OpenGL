#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Texture.h"

class Object {
protected:
	GLFWwindow* window;
	Camera* camera;
	Shader shader;
	VAO* _VAO;
	VBO _VBO;
	EBO _EBO;

	void Init();
public:
	Object(VAO* _VAO, Camera* camera, GLFWwindow* window) {
		this->_VAO = _VAO;
		this->camera = camera;
		this->window = window;
	}

	void Draw();
	void Control(int key) {}
	void Dispose();
};