#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

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

void Triangle(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	float timeValue = glfwGetTime();
	float redValue = sin(5.0f * timeValue) / 2.0f + 0.5f;
	float blueValue = sin(10.0f * timeValue) / 2.0f + 0.5f;
	float scale = 0.5f * sin(timeValue) + 1;
	float rotate = 5 * timeValue;
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
void Circle(Shader shaderProgram, VAO _VAO, EBO _EBO) {
	shaderProgram.Activate();
	_VAO.Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
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



		// Generates Shader object using shaders defualt.vert and default.frag
		Shader shaderProgram1("square.vert", "square.frag");
		Shader shaderProgram2("circle.vert", "circle.frag");
		Shader shaderProgram("default.vert", "default.frag");
	


		// Generates Vertex Array Object and binds it
		VAO VAO1;
		VAO1.Bind();
		printf("VAO%p\n", &VAO1.ID);

		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO1(vertices, sizeof(vertices));
		// Generates Element Buffer Object and links it to indices
		EBO EBO1(indices, sizeof(indices));



		// Links VBO to VAO
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		VAO1.Bind();
		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO2(vertices_square, sizeof(vertices_square));
		// Generates Element Buffer Object and links it to indices
		EBO EBO2(indices_square, sizeof(indices_square));
		VAO1.LinkAttrib(VBO2, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	
		// Unbind all to prevent accidentally modifying them
		VAO1.Unbind();
		VBO2.Unbind();
		EBO2.Unbind();

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
		for (int i = 6; i < 600; i+=6) {
			vertices_circle[i + 0] = 0.3f * sin(angle * (3.14f / 180.0f));
			vertices_circle[i + 1] = 0.3f * cos(angle * (3.14f / 180.0f));
			vertices_circle[i + 2] = 0.0f;
			vertices_circle[i + 3] = col;
			vertices_circle[i + 4] = col;
			vertices_circle[i + 5] = 0.0f;
			angle += step;
			col += x;
			printf("(%f, %f, %f, %f, %f, %f)\n", vertices_circle[i + 0], vertices_circle[i + 1], vertices_circle[i + 2], vertices_circle[i + 3], vertices_circle[i + 4], vertices_circle[i + 5]);
		}
		printf("ебало");
		GLuint indicies_circle[150] = {};
		int plus = 1;
		int adjust = 0;
		for (int i = 0; i < 147; i+=3) {
			indicies_circle[i + 0] = 0;
			indicies_circle[i + 1] = plus;
			indicies_circle[i + 2] = 1 + plus;
			plus++;
			adjust++;
		}
		for (int i = 0; i < 150; i += 3) {
			printf("(%d, %d, %d)\n", indicies_circle[i + 0], indicies_circle[i + 1], indicies_circle[i + 2]);
		}

		VAO1.Bind();
		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO3(vertices_circle, sizeof(vertices_circle));
		// Generates Element Buffer Object and links it to indices
		EBO EBO3(indicies_circle, sizeof(indicies_circle));
		VAO1.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO3, 4, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		// Unbind all to prevent accidentally modifying them
		VAO1.Unbind();
		VBO3.Unbind();
		EBO3.Unbind();


		// Main while loop
		while (!glfwWindowShouldClose(window))
		{
			// Specify the color of the background
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and assign the new color to it
			glClear(GL_COLOR_BUFFER_BIT);
			// Tell OpenGL which Shader Program we want to use
			Square(shaderProgram1, VAO1, EBO2);
			Circle(shaderProgram2, VAO1, EBO3);
			Triangle(shaderProgram, VAO1, EBO1);
		
			// Swap the back buffer with the front buffer
			glfwSwapBuffers(window);
			// Take care of all GLFW events
			glfwPollEvents();
		}

		// Delete all the objects we've created
		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
		VBO2.Delete();
		EBO2.Delete();
		VBO3.Delete();
		EBO3.Delete();
		shaderProgram.Delete();
		// Delete window before ending the program
		glfwDestroyWindow(window);
		// Terminate GLFW before ending the program
		glfwTerminate();
	}
	catch(std::exception e){
		
	}
	return 0;
}