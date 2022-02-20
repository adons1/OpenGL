#include "Square.h"

void Square::Init() {
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
	shader = Shader("square.vert", "square.frag");
	_VAO->Bind();

	_VBO = VBO(vertices_square, sizeof(vertices_square));

	_EBO = EBO(indices_square, sizeof(indices_square));
	_VAO->LinkAttrib(_VBO, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void Square::Draw() {
	float timeValue = glfwGetTime();
	float rotate = 2.0f * timeValue;
	GLuint rotateID = glGetUniformLocation(shader.ID, "rotate");
	shader.Activate();
	glUniform1f(rotateID, rotate);

	_VAO->Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}

void Square::Dispose() {
	_VBO.Delete();
	_EBO.Delete();
	shader.Delete();
}
