#pragma once
#include "Object.h"
#include "Light.h"

class Pyramide : public Object {
protected:
	Texture texture;
	DotLight* light;

	unsigned int width;
	unsigned int height;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	void Init();
public:
	Pyramide(){}
	Pyramide(VAO* _VAO, Camera* camera, GLFWwindow* window, const unsigned int width, const unsigned int height, int pyramideId, DotLight* light) : Object(_VAO, camera, window, pyramideId) {
		Init();
		this->width = width;
		this->height = height;
		this->light = light;
	}

	void Draw();
	void Control(int key);

	void Dispose() {
		Object::Dispose();
	}
};