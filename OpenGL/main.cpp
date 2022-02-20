#include<iostream>
#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Texture.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Camera.h"
#include "Triangle.h"
#include "Square.h"
#include "TexturedSquare.h"
#include "Circle.h"
#include "Observable.h"
#include "Pyramide.h"
#include "Light.h"
#include "LightningCube.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	Observable::Notify(key);
}

int main()
{
	try {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		 
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Adons", NULL, NULL);
		
		glfwSetKeyCallback(window, keyCallback);
		 
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		 
		glfwMakeContextCurrent(window);

		gladLoadGL();
		 
		glViewport(0, 0, width, height);

		VAO _VAO;

		Camera camera(width, height, glm::vec3(20.0f, 20.0f, 20.0f));
		DotLight light(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

#pragma region Инициализируем фигуры
		Square square(&_VAO, &camera, window);
		Triangle triangle(&_VAO, &camera, window);
		TexturedSquare texturedSquare(&_VAO, &camera, window);
		Circle circle(&_VAO, &camera, window);
		LightningCube lightningCube(&_VAO, &camera, window, &light);

		int number_of_pyramides = 11;
		Pyramide* pyramides = new Pyramide[number_of_pyramides];
		for (float i = 0; i < number_of_pyramides; i++) {
			pyramides[(int)i] = Pyramide(&_VAO, &camera, window, width, height, i, &light);
		}
#pragma endregion
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			light.Recalc();

			camera.Inputs(window);
			camera.updateMatrix(45.0f, 0.1f, 1000.0f);


			for (int i = 0; i < number_of_pyramides; i++) {
				pyramides[i].Draw();
			}
			lightningCube.Draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		_VAO.Delete();

		triangle.Dispose();
		square.Dispose();
		texturedSquare.Dispose();
		circle.Dispose();
		lightningCube.Dispose();
		for (float i = 0; i < number_of_pyramides; i++) {
			pyramides[(int)i].Dispose();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();  
	}
	return 0;
}
