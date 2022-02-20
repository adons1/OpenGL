#pragma once
#include "Object.h"
#include "Light.h"

class LightningCube : public Object {
protected:
	Texture texture;
	DotLight* light;

	unsigned int width;
	unsigned int height;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	void Init();
public:
	LightningCube() {}
	LightningCube(VAO* _VAO, Camera* camera, GLFWwindow* window, DotLight* light) : Object(_VAO, camera, window) {
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