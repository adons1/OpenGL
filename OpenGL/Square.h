#pragma once
#include "Object.h"

class Square : public Object {
protected:
	void Init();
public:
	Square(VAO* _VAO, Camera* camera, GLFWwindow* window) : Object(_VAO, camera, window) {
		Init();
	}

	void Draw();
	void Dispose() {
		Object::Dispose();
	}
};