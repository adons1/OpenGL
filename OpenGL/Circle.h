#pragma once
#include "Object.h"
#include "Observable.h"

class Circle : Object {
protected:
	GLfloat angle_circle_rotate, x_circle_move, y_circle_move, z_circle_move = 0.0f;
	float speed = 0.01f;
	void Init();
public:
	Circle(VAO* _VAO, Camera* camera, GLFWwindow* window) : Object(_VAO, camera, window) {
		Init();


		//Observable::Add(this);
	}

	void Draw();
	void Control(int key);

	void Dispose();
};