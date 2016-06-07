#include "Model.hpp"

namespace fruitjuice {
	Model::Model() {
		modelView = glm::mat4(1.0f);
	}

	Model::~Model() {
	}

	void Model::Tick() {
		rotation += 0.01f;
		modelView = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 1, 0));
	}

	void Model::LoadVertexData(const std::vector<const GLfloat> vertices) {
		this->vertices = vertices;
		glGenBuffers(1, &vertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);
	}

	void Model::LoadIndexData(const std::vector<const GLuint> indices) {
		this->indices = indices;
		glGenBuffers(1, &indexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	}

	void Model::Draw(Camera& camera) const {
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera.getCamera()));
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelView));

		glEnableVertexAttribArray(positionLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(positionLocation);
	}
}