#pragma once
#include "Object.h"

class TexturedSquare : Object {
protected:
	Texture texture;
	void Init();
public:
	TexturedSquare(VAO* _VAO, Camera* camera, GLFWwindow* window) : Object(_VAO, camera, window) {
		Init();
	}

	void Draw();
	void Dispose();
};