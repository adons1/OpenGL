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
	int object_id;
	GLFWwindow* window;
	Camera* camera;
	Shader shader;
	VAO* _VAO;
	VBO _VBO;
	EBO _EBO;

	void Init();
public:
	Object(){}
	Object(VAO* _VAO, Camera* camera, GLFWwindow* window, int object_id = 0) {
		this->_VAO = _VAO;
		this->camera = camera;
		this->window = window;
		this->object_id = object_id;
	}

	void Draw();
	virtual void Control(int key) {
	};
	void Dispose() {
		_VBO.Delete();
		_EBO.Delete();
		shader.Delete();
	}
};