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



const unsigned int width = 1920;
const unsigned int height = 1080;

class Figure{
public:
	Shader shader;
	VBO _VBO;
	EBO _EBO;
};
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
	(*VAO1).Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	(*VAO1).LinkAttrib(lightVBO, 12, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	(*VAO1).Unbind();
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
Figure TriangleInit(VAO* VAO1) {
	 
	GLfloat vertices[] =
	{  
		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,  
		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,  
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f,  
		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,  
		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,  
		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f   
	};
	 
	GLuint indices[] =
	{
		0, 3, 5,  
		3, 2, 4,  
		5, 4, 1  
	};
	Shader shaderProgram("default.vert", "default.frag");
	(*VAO1).Bind();
	 
	VBO VBO1(vertices, sizeof(vertices));
	 
	EBO EBO1(indices, sizeof(indices));

	 
	(*VAO1).LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	(*VAO1).Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	Figure figure{ shaderProgram, VBO1, EBO1 };
	return figure;
}
void Triangle(Shader shaderProgram, VAO _VAO, EBO _EBO, Camera camera, GLFWwindow* window) {
	

	float timeValue = glfwGetTime();
	float redValue = sin(5.0f * timeValue) / 2.0f + 0.5f;
	float blueValue = sin(10.0f * timeValue) / 2.0f + 0.5f;
	float scale = 0.5f * sin(timeValue) + 1;
	float rotate = 5.0f * timeValue;
	GLuint colorID = glGetUniformLocation(shaderProgram.ID, "Color1");
	GLuint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint rotateID = glGetUniformLocation(shaderProgram.ID, "rotate");

	shaderProgram.Activate();
	camera.Matrix(shaderProgram, "camMatrix");
	camera.updateMatrix(45.0f, 0.1f, 1000.0f);
	glUniform4f(colorID, redValue, 0, blueValue, 1.0f);
	glUniform1f(scaleID, scale);
	glUniform1f(rotateID, rotate);
	 
	_VAO.Bind();
	_EBO.Bind();
	 
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


Figure SquareInit(VAO* VAO1) {
	GLfloat vertices_square[] =
	{  
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,	0.5f, 0.0f
	};

	GLuint indices_square[] =
	{
		0, 1, 3, 2, 1 , 3, 0
	};
	Shader shaderProgram1("square.vert", "square.frag");
	(*VAO1).Bind();
	 
	VBO VBO2(vertices_square, sizeof(vertices_square));
	 
	EBO EBO2(indices_square, sizeof(indices_square));
	(*VAO1).LinkAttrib(VBO2, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


	 
	(*VAO1).Unbind();
	VBO2.Unbind();
	EBO2.Unbind();
	Figure figure{ shaderProgram1, VBO2, EBO2 };
	return figure;
}
void Square(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	float timeValue = glfwGetTime();
	float rotate = 2.0f * timeValue;
	GLuint rotateID = glGetUniformLocation(shaderProgram.ID, "rotate");
	shaderProgram.Activate();
	glUniform1f(rotateID, rotate);

	_VAO.Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}

FigureWithTexture SquareWithTextureInit(VAO* VAO1) {
	Shader shaderProgram("square_textured.vert", "square_textured.frag");
	float vertices[] = {
		 
		-0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,    
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 15.0f,    
		0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  15.0f, 15.0f,    
		0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  15.0f, 0.0f     
	};
	unsigned int indices[] = {
	   0, 2, 1,  
	   0, 3, 2, 0   
	};
	 
	(*VAO1).Bind();

	 
	VBO VBO4(vertices, sizeof(vertices));
	 
	EBO EBO4(indices, sizeof(indices));

	(*VAO1).LinkAttrib(VBO4, 3, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO4, 4, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	(*VAO1).LinkAttrib(VBO4, 5, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	(*VAO1).Unbind();
	VBO4.Unbind();
	EBO4.Unbind();
	 
	 
	Texture square("awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	FigureWithTexture figure {shaderProgram, VBO4, EBO4, square };
	return figure;
}
void SquareWithTexture(Shader shaderProgram, VAO _VAO, EBO _EBO, Texture square) {
	float timeValue = glfwGetTime();
	float rotate = 2.0f * timeValue;
	GLuint rotateID = glGetUniformLocation(shaderProgram.ID, "rotate");
	square.texUnit(shaderProgram, "tex0", 0);
	glUniform1f(rotateID, rotate);
	square.Bind();
	_VAO.Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);
	
	_EBO.Unbind();
}


GLfloat angle_circle_rotate, x_circle_move, y_circle_move, z_circle_move = 0.0f;
float speed = 0.01f;
Figure CircleInit(VAO* VAO1) {
	Shader shaderProgram2("circle.vert", "circle.frag");
	GLfloat vertices_circle[606] = {};
	GLfloat step = 360.0f / 40.f;
	GLfloat angle = 0;
	vertices_circle[0] = 0.0f;
	vertices_circle[1] = 0.0f;
	vertices_circle[2] = 0.0f;
	vertices_circle[3] = 1.0f;
	vertices_circle[4] = 1.0f;
	vertices_circle[5] = 0.0f;
	float x = 1.0f / 100.0f;
	float col = 0.0f;
	for (int i = 6; i < 600; i += 6) {
		vertices_circle[i + 0] = 0.3f * sin(angle * (3.14f / 180.0f));
		vertices_circle[i + 1] = 0.3f * cos(angle * (3.14f / 180.0f));
		vertices_circle[i + 2] = 0.0f;
		vertices_circle[i + 3] = col;
		vertices_circle[i + 4] = col;
		vertices_circle[i + 5] = 0.0f;
		angle += step;
		col += x;
		 
	}
	GLuint indicies_circle[150] = {};
	int plus = 1;
	int adjust = 0;
	for (int i = 0; i < 147; i += 3) {
		indicies_circle[i + 0] = 0;
		indicies_circle[i + 1] = plus;
		indicies_circle[i + 2] = 1 + plus;
		plus++;
		adjust++;
	}
	for (int i = 0; i < 150; i += 3) {
		 
	}

	(*VAO1).Bind();
	 
	VBO VBO3(vertices_circle, sizeof(vertices_circle));
	 
	EBO EBO3(indicies_circle, sizeof(indicies_circle));
	(*VAO1).LinkAttrib(VBO3, 6, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO3, 7, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	 
	(*VAO1).Unbind();
	VBO3.Unbind();
	EBO3.Unbind();
	Figure figure{ shaderProgram2, VBO3, EBO3 };
	return figure;
}
void Circle(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	GLfloat move_circle_id = glGetUniformLocation(shaderProgram.ID, "move");
	shaderProgram.Activate();
	_VAO.Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
	glUniform3f(move_circle_id, x_circle_move, y_circle_move, z_circle_move);
	 
	_EBO.Unbind();
}
void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (key == GLFW_KEY_A) {
		x_circle_move += -speed;
		printf("A ");
	}
	if (key == GLFW_KEY_D) {
		x_circle_move += speed;
		printf("D ");
	}
	if (key == GLFW_KEY_W) {
		y_circle_move += speed;
		printf("W ");
	}
	if (key == GLFW_KEY_S) {
		y_circle_move += -speed;
		printf("S ");
	}
	if (key == GLFW_KEY_SPACE) {
		z_circle_move += 0.01f;
		printf("S ");
		 
	}
	if (key == GLFW_KEY_UP) {
		if (speed < 0.2f) {
			speed += 0.01f;
		}
		printf("UP ");
	}
	if (key == GLFW_KEY_DOWN) {
		if (speed > 0.01f) {
			speed += -0.01f;
		}
		printf("DOWN ");
	}
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

	(*VAO1).Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	(*VAO1).LinkAttrib(VBO1, 8, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO1, 9, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	(*VAO1).LinkAttrib(VBO1, 10, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	(*VAO1).LinkAttrib(VBO1, 11, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	 
	(*VAO1).Unbind();
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
		Figure triangele = TriangleInit(&VAO1);
		Figure square = SquareInit(&VAO1);
		FigureWithTexture square_with_texture= SquareWithTextureInit(&VAO1);
		Figure circle = CircleInit(&VAO1);
		Figure lightning_cube = LightningCubeInit(&VAO1);
		
		int number_of_pyramides = 11;
		FigureWithTexture* pyramides = new FigureWithTexture[number_of_pyramides];
		for (float i = 0; i < number_of_pyramides; i++) {
			pyramides[(int)i] = PyramideInit(&VAO1, "emblema_mai.png");
		}
#pragma endregion
		Camera camera(width, height, glm::vec3(20.0f, 20.0f, 20.0f));

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

			for (int i = 0; i < number_of_pyramides; i++) {
				Pyramide(pyramides[i].shader, VAO1, pyramides[i]._EBO, pyramides[i].texture, camera, window,  &lightColor, &lightPos, glm::vec3(5.0f * cos(i*36.0f), 5.0f * sin(i * 36.0f), 0.0f), 1.0f);
			}
			LightningCube(lightning_cube.shader, VAO1, lightning_cube._EBO, camera, window, &lightColor, &lightPos, 10.0f * sin(5 * timeValue));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		VAO1.Delete();

		triangele._VBO.Delete();
		triangele._EBO.Delete();
		circle._VBO.Delete();
		circle._EBO.Delete();
		square._VBO.Delete();
		square._EBO.Delete();
		square_with_texture._VBO.Delete();
		square_with_texture._EBO.Delete();

		triangele.shader.Delete();
		circle.shader.Delete();
		square.shader.Delete();
		square_with_texture.shader.Delete();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();  
	}
	return 0;
}
