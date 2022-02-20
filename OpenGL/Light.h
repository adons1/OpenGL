#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <vector>

class DotLight {
public:
	glm::vec3 Position;
	glm::vec4 Color;

	DotLight(glm::vec3 position, glm::vec4 color) {
		Position = position;
		Color = color;
	}

	void Recalc() {
		float timeValue = glfwGetTime();
		Position = glm::vec3(0.0f, 0.0f, 10.0f * sin(5 * timeValue));
	}
};