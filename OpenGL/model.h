#pragma once
#include "Object.h"
#include "Light.h"

class Model : public Object {
protected:
	Texture texture;
	DotLight* light;
	
	std::string objPath;
	std::string texturePath;

	unsigned int width;
	unsigned int height;
	int szIndicies;

	glm::vec3 initialPosition;
	glm::vec3 color;

	bool showColor;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	void Init();
public:
	Model() {}
	Model(VAO* _VAO,
		Camera* camera,
		GLFWwindow* window,
		DotLight* light,
		std::string objPath,
		std::string texturePath,
		bool showColor = true,
		glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f)) : Object(_VAO, camera, window) {
		
		this->width = width;
		this->height = height;
		this->light = light;

		this->color = color;
		this->showColor = showColor;

		this->objPath = objPath;
		this->texturePath = texturePath;

		this->initialPosition = initialPosition;

		Init();
	}

	void Draw();
	std::tuple<GLfloat*, GLuint*> SimpleLoad(std::string objPath, int* szIndicies, int* szVerticies);
	void Control(int key);

	void Dispose() {
		Object::Dispose();
	}
};