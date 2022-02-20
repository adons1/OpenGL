#include "Triangle.h"

void Triangle::Init() {
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
	shader = Shader("default.vert", "default.frag");
	_VAO->Bind();

	_VBO = VBO(vertices, sizeof(vertices));
	_EBO = EBO(indices, sizeof(indices));

	_VAO->LinkAttrib(_VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	_VAO->LinkAttrib(_VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void Triangle::Draw() {
	float timeValue = glfwGetTime();
	float redValue = sin(5.0f * timeValue) / 2.0f + 0.5f;
	float blueValue = sin(10.0f * timeValue) / 2.0f + 0.5f;
	float scale = 0.5f * sin(timeValue) + 1;
	float rotate = 5.0f * timeValue;
	GLuint colorID = glGetUniformLocation(shader.ID, "Color1");
	GLuint scaleID = glGetUniformLocation(shader.ID, "scale");
	GLuint rotateID = glGetUniformLocation(shader.ID, "rotate");

	shader.Activate();
	camera->Matrix(shader, "camMatrix");
	camera->updateMatrix(45.0f, 0.1f, 1000.0f);
	glUniform4f(colorID, redValue, 0, blueValue, 1.0f);
	glUniform1f(scaleID, scale);
	glUniform1f(rotateID, rotate);

	_VAO->Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}

void Triangle::Dispose() {
	_VBO.Delete();
	_EBO.Delete();
	shader.Delete();
}
