#pragma once
#include "Object.h"

class Triangle : public Object {
protected:
	void Init();
public:
	Triangle(VAO* _VAO, Camera* camera, GLFWwindow* window) : Object(_VAO, camera, window) {
		Init();
	}

	void Draw();
	void Dispose() {
		Object::Dispose();
	}
};