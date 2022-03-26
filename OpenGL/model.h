#pragma once
#include "Object.h"
#include "Light.h"

class Model : public Object {
protected:
	Texture texture;
	DotLight* light;

	std::string objPath;

	unsigned int width;
	unsigned int height;
	int szIndicies;

	glm::vec3 initialPosition;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	void Init();
public:
	Model() {}
	Model(VAO* _VAO, Camera* camera, GLFWwindow* window, DotLight* light, std::string objPath, glm::vec3 initialPosition) : Object(_VAO, camera, window) {
		
		this->width = width;
		this->height = height;
		this->light = light;

		this->objPath = objPath;

		this->initialPosition = initialPosition;

		Init();
	}

	void Draw();
	void Control(int key);

	void Dispose() {
		Object::Dispose();
	}
};