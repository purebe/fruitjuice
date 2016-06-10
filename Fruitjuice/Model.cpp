#include "Model.hpp"

namespace fruitjuice {
	Model::Model() {
		modelView = glm::mat4(1.0f);
	}
	
	Model::~Model() {
	}

	void Model::LoadVertices(const std::vector<const GLfloat> vertices) {
		this->vertices = vertices;
		glGenBuffers(1, &vertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);
	}

	void Model::LoadNormals(const std::vector<const GLfloat> normals) {
		this->normals = normals;
		glGenBuffers(1, &normalBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(GLfloat), &this->normals[0], GL_STATIC_DRAW);
	}

	void Model::LoadIndices(const std::vector<const GLuint> indices) {
		this->indices = indices;
		glGenBuffers(1, &indexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	}

	void Model::Draw(const Camera& camera) const {
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera.getMVP()));
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelView));

		glEnableVertexAttribArray(positionLocation);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(normalLocation);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(positionLocation);
		glDisableVertexAttribArray(normalLocation);
	}
}