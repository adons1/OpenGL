#include "model.h"
#include "ModelLoader.h"

void Model::Init() {
	shader = Shader("model.vert", "model.frag");
	objl::Loader loader;
	loader.LoadFile(objPath);

	GLfloat* verticies = new GLfloat[6 * loader.LoadedVertices.size()];
	GLuint* indices = new GLuint[loader.LoadedIndices.size()];

	szIndicies = loader.LoadedIndices.size();

	for (int i = 0; i < loader.LoadedVertices.size(); i++) {
		verticies[6 * i + 0] = loader.LoadedVertices[i].Position.X;
		verticies[6 * i + 1] = loader.LoadedVertices[i].Position.Y;
		verticies[6 * i + 2] = loader.LoadedVertices[i].Position.Z;
	
		verticies[6 * i + 3] = loader.LoadedVertices[i].Normal.X;
		verticies[6 * i + 4] = loader.LoadedVertices[i].Normal.Y;
		verticies[6 * i + 5] = loader.LoadedVertices[i].Normal.Z;
		//std::cout << verticies[3 * i + 0] << "\t" << verticies[3 * i + 1] << "\t" << verticies[3 * i + 2] << std::endl;
	}

	for (int i = 0; i < loader.LoadedIndices.size(); i++) {
		indices[i] = loader.LoadedIndices[i];
		//std::cout << indices[i] << std::endl;
	}

	
	_VAO->Bind();
	_VBO = VBO(verticies, 6 * sizeof(float) * loader.LoadedVertices.size());
	_EBO = EBO(indices, sizeof(int) * loader.LoadedIndices.size());

	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); Shader::shaderLocationPointer++;
	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); Shader::shaderLocationPointer++;

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}
void Model::Draw() {
	shader.Activate();

	glm::vec4* lightColor = &(light->Color);
	glm::vec3* lightPos = &(light->Position);

	

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera->Position.x, camera->Position.y, camera->Position.z);
	camera->Matrix(shader, "camMatrix");
	camera->updateMatrix(45.0f, 0.1f, 80000.0f);

	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::translate(view, initialPosition);

	int positionLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(positionLoc, 1, GL_FALSE, glm::value_ptr(position));
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos->x, lightPos->y, lightPos->z);

	_VAO->Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, szIndicies, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


void Model::Control(int key) {

}