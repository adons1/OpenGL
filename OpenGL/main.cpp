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
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "TexturedSquare.h"
#include "Circle.h"
#include "Observable.h"

const unsigned int width = 1920;
const unsigned int height = 1080;


class FigureWithTexture {
public:
	FigureWithTexture():shader(Shader()),_VBO(VBO()), _EBO(EBO()), texture(Texture()){}
	FigureWithTexture(Shader shader1, VBO _VBO1, EBO _EBO1, Texture texture1):shader(shader1),_VBO(_VBO1), _EBO(_EBO1), texture(texture1){}
	Shader shader;
	VBO _VBO;
	EBO _EBO;
	Texture texture;
};
Figure LightningCubeInit(VAO* VAO1) {
	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
	
	Shader lightShader("lightning.vert", "lightning.frag");
	VAO1->Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	VAO1->LinkAttrib(lightVBO, 12, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	VAO1->Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();
	Figure figure{ lightShader, lightVBO, lightEBO };
	return figure;
}
void LightningCube(Shader shaderProgram, VAO _VAO, EBO _EBO, Camera camera, GLFWwindow* window, glm::vec4* lightColor, glm::vec3* lightPos, GLfloat scale) {
	shaderProgram.Activate();
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, *lightPos);
	camera.Matrix(shaderProgram, "camMatrix");
	camera.updateMatrix(45.0f, 0.1f, 1000.0f);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), scale);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);

	_VAO.Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}

FigureWithTexture PyramideInit(VAO* VAO1, const char* image) {
	Shader shaderProgram("pyramide.vert", "pyramide.frag");
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	VAO1->Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1->LinkAttrib(VBO1, 8, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1->LinkAttrib(VBO1, 9, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->LinkAttrib(VBO1, 10, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1->LinkAttrib(VBO1, 11, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	 
	VAO1->Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	Texture texture(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	FigureWithTexture figure{ shaderProgram, VBO1, EBO1, texture };
	return figure;
}

float rotation = 0.0f;
double prevTime = glfwGetTime();
void Pyramide(Shader shaderProgram, VAO _VAO, EBO _EBO, Texture texture, Camera camera, GLFWwindow* window, glm::vec4* lightColor, glm::vec3* lightPos, glm::vec3 shift, GLuint scale = 0.5f) {
	shaderProgram.Activate();
	
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shaderProgram, "camMatrix");
	camera.updateMatrix(45.0f, 0.1f, 1000.0f);
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	double crntTime = glfwGetTime();
	if (crntTime - prevTime >= 1 / 60)
	{
		rotation += 0.5f/10.0f;
		prevTime = crntTime;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(view, shift);
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1f(uniID, scale);

	
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos->x, lightPos->y, lightPos->z);

	texture.Bind();

	_VAO.Bind();
	_EBO.Bind();
	 
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


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
#pragma region Инициализируем фигуры
		VAO VAO1;


		
		Figure lightning_cube = LightningCubeInit(&VAO1);
		
		int number_of_pyramides = 11;
		FigureWithTexture* pyramides = new FigureWithTexture[number_of_pyramides];
		for (float i = 0; i < number_of_pyramides; i++) {
			pyramides[(int)i] = PyramideInit(&VAO1, "emblema_mai.png");
		}
#pragma endregion
		Camera camera(width, height, glm::vec3(20.0f, 20.0f, 20.0f));

		Square square(&VAO1, &camera, window);
		Triangle triangle(&VAO1, &camera, window);
		TexturedSquare texturedSquare(&VAO1, &camera, window);
		Circle circle(&VAO1, &camera, window);

		float* randomshifts = new float[number_of_pyramides];
		for (int i = 0; i < number_of_pyramides; i++) {
			*(randomshifts + i) = (rand() % 10 - 5);
		}

		

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			float timeValue = glfwGetTime();
			glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 10.0f * sin(5 * timeValue));

			camera.Inputs(window);
			camera.updateMatrix(45.0f, 0.1f, 1000.0f);

			circle.Draw();

			for (int i = 0; i < number_of_pyramides; i++) {
				Pyramide(pyramides[i].shader, VAO1, pyramides[i]._EBO, pyramides[i].texture, camera, window,  &lightColor, &lightPos, glm::vec3(5.0f * cos(i*36.0f), 5.0f * sin(i * 36.0f), 0.0f), 1.0f);
			}
			LightningCube(lightning_cube.shader, VAO1, lightning_cube._EBO, camera, window, &lightColor, &lightPos, 10.0f * sin(5 * timeValue));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		VAO1.Delete();

		triangle.Dispose();
		square.Dispose();
		texturedSquare.Dispose();
		circle.Dispose();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();  
	}
	return 0;
}
