#include "LightningCube.h"

void LightningCube::Init() {
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

	shader = Shader("lightning.vert", "lightning.frag");
	_VAO->Bind();
	_VBO = VBO(lightVertices, sizeof(lightVertices));
	_EBO = EBO(lightIndices, sizeof(lightIndices));
	_VAO->LinkAttrib(_VBO, 12, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void LightningCube::Draw() {
	shader.Activate();

	glm::vec4* lightColor = &(light->Color);
	glm::vec3* lightPos = &(light->Position);

	GLfloat scale = 10.0f * sin(5 * glfwGetTime());

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, *lightPos);
	camera->Matrix(shader, "camMatrix");
	camera->updateMatrix(45.0f, 0.1f, 1000.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "scale"), scale);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);

	_VAO->Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


void LightningCube::Control(int key) {

}