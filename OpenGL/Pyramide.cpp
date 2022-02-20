#include "Pyramide.h"

void Pyramide::Init() {
	shader = Shader("pyramide.vert", "pyramide.frag");
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

	_VAO->Bind();

	_VBO = VBO(vertices, sizeof(vertices));
	_EBO = EBO(indices, sizeof(indices));

	_VAO->LinkAttrib(_VBO, 8, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	_VAO->LinkAttrib(_VBO, 9, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO->LinkAttrib(_VBO, 10, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	_VAO->LinkAttrib(_VBO, 11, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
	texture = Texture("emblema_mai.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shader, "tex0", 0);

	glEnable(GL_DEPTH_TEST);
}

float rotation = 0.0f;
double prevTime = glfwGetTime();
void Pyramide::Draw() {
	shader.Activate();

	glm::vec4* lightColor = &(light->Color);
	glm::vec3* lightPos = &(light->Position);

	glm::vec3 shift = glm::vec3(5.0f * cos(object_id * 36.0f), 5.0f * sin(object_id * 36.0f), 0.0f);
	GLfloat scale = 1.0f;

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera->Position.x, camera->Position.y, camera->Position.z);
	camera->Matrix(shader, "camMatrix");
	camera->updateMatrix(45.0f, 0.1f, 1000.0f);
	GLuint uniID = glGetUniformLocation(shader.ID, "scale");

	double crntTime = glfwGetTime();
	if (crntTime - prevTime >= 1 / 60)
	{
		rotation += 0.5f / 10.0f;
		prevTime = crntTime;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(view, shift);
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(shader.ID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1f(uniID, scale);


	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos->x, lightPos->y, lightPos->z);

	texture.Bind();

	_VAO->Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}
void Pyramide::Control(int key) {

}