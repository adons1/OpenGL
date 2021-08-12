#include<iostream>
#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


class Figure{
public:
	Shader shader;
	VBO _VBO;
	EBO _EBO;
};


Figure TriangleInit(VAO* VAO1) {
	// Vertices coordinates
	GLfloat vertices[] =
	{ //               COORDINATES                  /     COLORS           //
		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
	};
	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};
	Shader shaderProgram("default.vert", "default.frag");
	(*VAO1).Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	(*VAO1).LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	(*VAO1).Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	Figure figure{ shaderProgram, VBO1, EBO1 };
	return figure;
}
void Triangle(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	float timeValue = glfwGetTime();
	float redValue = sin(5.0f * timeValue) / 2.0f + 0.5f;
	float blueValue = sin(10.0f * timeValue) / 2.0f + 0.5f;
	float scale = 0.5f * sin(timeValue) + 1;
	float rotate = 5.0f * timeValue;
	GLuint colorID = glGetUniformLocation(shaderProgram.ID, "Color1");
	GLuint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint rotateID = glGetUniformLocation(shaderProgram.ID, "rotate");

	shaderProgram.Activate();
	glUniform4f(colorID, redValue, 0, blueValue, 1.0f);
	glUniform1f(scaleID, scale);
	glUniform1f(rotateID, rotate);
	// Bind the VAO so OpenGL knows to use it
	_VAO.Bind();
	_EBO.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


Figure SquareInit(VAO* VAO1) {
	GLfloat vertices_square[] =
	{ //               COORDINATES                  /    
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
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(vertices_square, sizeof(vertices_square));
	// Generates Element Buffer Object and links it to indices
	EBO EBO2(indices_square, sizeof(indices_square));
	(*VAO1).LinkAttrib(VBO2, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


	// Unbind all to prevent accidentally modifying them
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


GLuint texture;
Figure SquareWithTextureInit(VAO* VAO1) {
	Shader shaderProgram("square_textured.vert", "square_textured.frag");
	float vertices[] = {
		// координаты        // цвета            // текстурные координаты
		-0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // верхняя правая
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 15.0f,   // нижняя правая
		0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  15.0f, 15.0f,   // нижняя левая
		0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  15.0f, 0.0f    // верхняя левая 
	};
	unsigned int indices[] = {
	   0, 2, 1, // первый треугольник
	   0, 3, 2, 0  // второй треугольник
	};
	//unsigned int VBO, EBO;
	(*VAO1).Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO4(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO4(indices, sizeof(indices));

	(*VAO1).LinkAttrib(VBO4, 3, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO4, 4, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	(*VAO1).LinkAttrib(VBO4, 5, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	(*VAO1).Unbind();
	VBO4.Unbind();
	EBO4.Unbind();
	//-----------------------------
	// Загрузка изображения, создание текстуры и генерирование мипмап-уровней
	int width, height, nrChannels;
	unsigned char* data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Загрузка и создание текстуры
	
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Установка параметров фильтрации текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Установка параметров наложения текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	
	Figure figure{ shaderProgram, VBO4, EBO4 };
	return figure;
}
void SquareWithTexture(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");

	float timeValue = glfwGetTime();
	float rotate = 2.0f * timeValue;
	GLuint rotateID = glGetUniformLocation(shaderProgram.ID, "rotate");
	
	shaderProgram.Activate();
	glUniform1f(tex0Uni, 0);
	glUniform1f(rotateID, rotate);
	glBindTexture(GL_TEXTURE_2D, texture);
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
		//printf("(%f, %f, %f, %f, %f, %f)\n", vertices_circle[i + 0], vertices_circle[i + 1], vertices_circle[i + 2], vertices_circle[i + 3], vertices_circle[i + 4], vertices_circle[i + 5]);
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
		//printf("(%d, %d, %d)\n", indicies_circle[i + 0], indicies_circle[i + 1], indicies_circle[i + 2]);
	}

	(*VAO1).Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO3(vertices_circle, sizeof(vertices_circle));
	// Generates Element Buffer Object and links it to indices
	EBO EBO3(indicies_circle, sizeof(indicies_circle));
	(*VAO1).LinkAttrib(VBO3, 6, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	(*VAO1).LinkAttrib(VBO3, 7, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
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
	//glUniform1f(move_circle_id, angle_circle_rotate);
	//x_circle_move = 0.0f;
	//y_circle_move = 0.0f;
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
		//z_circle_move += 0.0f;
	}
	//if (key == GLFW_KEY_E) {
	//	y_circle_move += speed;
	//	printf("W ");
	//}
	//if (key == GLFW_KEY_Q) {
	//	y_circle_move += -speed;
	//	printf("S ");
	//}
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


int main()
{
	try {
		
	
		// Initialize GLFW
		glfwInit();

		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
		GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL_Adons", NULL, NULL);
		glfwSetKeyCallback(window, keyCallback);
		// Error check if the window fails to create
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, 800, 800);

		// Generates Vertex Array Object and binds it

#pragma region Инициализируем фигуры
		//-----------------------------------------------------------------------------------------------------------------------------------
		VAO VAO1;
		//-------ИНИЦИИРУЕМ ТРЕУГОЛЬНИК----------------------------------------------------------
		Figure triangele = TriangleInit(&VAO1);
		//-------ИНИЦИИРУЕМ ТРЕУГОЛЬНИК----------------------------------------------------------
		//-------ИНИЦИИРУЕМ КВАДРАТ--------------------------------------------------------------
		Figure square = SquareInit(&VAO1);
		//-------ИНИЦИИРУЕМ КВАДРАТ----------------------------------------------------------
				//-------ИНИЦИИРУЕМ КВАДРАТ С ТЕКСТУРКОЙ--------------------------------------------------------------
		Figure square_with_texture= SquareWithTextureInit(&VAO1);
		//-------ИНИЦИИРУЕМ КВАДРАТ С ТЕКСТУРКОЙ----------------------------------------------------------
		//-------ИНИЦИИРУЕМ КРУГ-------------------------------------------------------------
		Figure circle = CircleInit(&VAO1);
		//-------ИНИЦИИРУЕМ КРУГ----------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------------------------------------
#pragma endregion

		 //Main while loop
		while (!glfwWindowShouldClose(window))
		{
			// Specify the color of the background
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and assign the new color to it
			glClear(GL_COLOR_BUFFER_BIT);

			// Tell OpenGL which Shader Program we want to use

			//Square(square.shader, VAO1, square._EBO);
			SquareWithTexture(square_with_texture.shader, VAO1, square_with_texture._EBO);
			Circle(circle.shader, VAO1, circle._EBO);
			Triangle(triangele.shader, VAO1, triangele._EBO);
			

			// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
			// Take care of all GLFW events
			glfwPollEvents();
		}

		// Delete all the objects we've created
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
		//glDeleteTextures(1, &texture);
		// Delete window before ending the program
		glfwDestroyWindow(window);
		 //Terminate GLFW before ending the program
		glfwTerminate();
	}
	catch (std::exception& e)
	{
		std::cout << e.what(); // For instance...
	}
	return 0;
}