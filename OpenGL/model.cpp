#include "model.h"
#include "ModelLoader.h"

std::tuple<GLfloat*, GLuint*> Model::SimpleLoad(std::string objPath, int* szIndicies, int* szVerticies) {
	
	objl::Loader loader;
	loader.LoadFile(objPath);

	GLfloat* verticies = new GLfloat[11 * loader.LoadedVertices.size()];
	GLuint* indices = new GLuint[loader.LoadedIndices.size()];

	*szIndicies = loader.LoadedIndices.size();
	*szVerticies = loader.LoadedVertices.size();

	for (int i = 0; i < loader.LoadedVertices.size(); i++) {
		verticies[11 * i + 0] = loader.LoadedVertices[i].Position.X;
		verticies[11 * i + 1] = loader.LoadedVertices[i].Position.Y;
		verticies[11 * i + 2] = loader.LoadedVertices[i].Position.Z;

		verticies[11 * i + 3] = loader.LoadedVertices[i].Normal.X;
		verticies[11 * i + 4] = loader.LoadedVertices[i].Normal.Y;
		verticies[11 * i + 5] = loader.LoadedVertices[i].Normal.Z;

		verticies[11 * i + 6] = loader.LoadedVertices[i].TextureCoordinate.X;
		verticies[11 * i + 7] = loader.LoadedVertices[i].TextureCoordinate.Y;

		verticies[11 * i + 8] = color.x;
		verticies[11 * i + 9] = color.y;
		verticies[11 * i + 10] = color.z;
		//std::cout << verticies[3 * i + 0] << "\t" << verticies[3 * i + 1] << "\t" << verticies[3 * i + 2] << std::endl;
	}

	for (int i = 0; i < loader.LoadedIndices.size(); i++) {
		indices[i] = loader.LoadedIndices[i];
		//std::cout << indices[i] << std::endl;
	}

	std::tuple<GLfloat*, GLuint*> vert_ind(verticies, indices);

	return vert_ind;
}

void Model::Init() {
	shader = Shader("model.vert", "model.frag");
	int szVerticies = 0;

	std::tuple<GLfloat*, GLuint*> vert_ind = SimpleLoad(objPath, &szIndicies, &szVerticies);

	GLfloat* verticies = std::get<0>(vert_ind);
	GLuint* indices = std::get<1>(vert_ind);

	_VAO->Bind();
	_VBO = VBO(verticies, 11 * sizeof(float) * szVerticies);
	_EBO = EBO(indices, sizeof(int) * szIndicies);

	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer++, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer++, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer++, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	_VAO->LinkAttrib(_VBO, Shader::shaderLocationPointer++, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	_VAO->Unbind();
	_VBO.Unbind();
	_EBO.Unbind();

	texture = Texture(texturePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shader, "tex0", 0);
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
	int showColor = glGetUniformLocation(shader.ID, "showColor");
	glUniform1i(showColor, showColor);

	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor->x, lightColor->y, lightColor->z, lightColor->w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos->x, lightPos->y, lightPos->z);

	texture.Bind();

	_VAO->Bind();
	_EBO.Bind();

	glDrawElements(GL_TRIANGLES, szIndicies, GL_UNSIGNED_INT, 0);
	_EBO.Unbind();
}


void Model::Control(int key) {

}