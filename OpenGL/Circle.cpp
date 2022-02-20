#include "Circle.h"

void Circle::Init() {
	shader = Shader("circle.vert", "circle.frag");
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

	_VAO->Bind();

	_VBO = VBO(vertices_circle, sizeof(vertices_circle));

	_EBO = EBO(indicies_circle, sizeof(indicies_circle));
	_VAO->LinkAttrib(_VBO, 6, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	_VAO->LinkAttrib(_VBO, 7, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void Circle::Draw() {
	GLfloat move_circle_id = glGetUniformLocation(shader.ID, "move");
	shader.Activate();
	_VAO->Bind();
	_EBO.Bind();
	glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
	glUniform3f(move_circle_id, x_circle_move, y_circle_move, z_circle_move);

	_EBO.Unbind();
}
void Circle::Control(int key) {
	printf("%d\n", key);
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
void Circle::Dispose() {
	_VBO.Delete();
	_EBO.Delete();
	shader.Delete();
}