#include "TexturedSquare.h"

void TexturedSquare::Init() {
	
	float vertices[] = {

		-0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		-0.5f,   0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 15.0f,
		 0.5f,   0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  15.0f, 15.0f,
		 0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  15.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2, 
		0
	};

	shader = Shader("square_textured.vert", "square_textured.frag");

	_VAO->Bind();

	_VBO = VBO(vertices, sizeof(vertices));

	_EBO = EBO(indices, sizeof(indices));

	texture = Texture("awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	_VAO->LinkAttrib(_VBO, 3, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO->LinkAttrib(_VBO, 4, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO->LinkAttrib(_VBO, 5, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void TexturedSquare::Draw() {
	float timeValue = glfwGetTime();
	float rotate = 2.0f * timeValue;
	GLuint rotateID = glGetUniformLocation(shader.ID, "rotate");
	texture.texUnit(shader, "tex0", 0);
	glUniform1f(rotateID, rotate);
	texture.Bind();
	_VAO->Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);

	_EBO.Unbind();
}
void TexturedSquare::Dispose() {
	_VBO.Delete();
	_EBO.Delete();
	shader.Delete();
}
