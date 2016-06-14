#include "Mesh.hpp"

namespace fruitjuice {
	Mesh::Mesh(std::string name, std::shared_ptr<Vertices> vertices, std::shared_ptr<Normals> normals, std::shared_ptr<Indices> indices,
		GLuint positionLocation, GLuint normalLocation, GLuint ambientLocation, GLuint diffuseLocation, GLuint opacityLocation) :
		name(name), vertices(vertices), normals(normals), indices(indices), ambientLocation(ambientLocation), diffuseLocation(diffuseLocation), opacityLocation(opacityLocation) {
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(GLfloat), &(*vertices)[0], GL_STATIC_DRAW);

		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals->size() * sizeof(GLfloat), &(*normals)[0], GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices->size() * sizeof(GLuint), &(*indices)[0], GL_STATIC_DRAW);

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(positionLocation);
		glEnableVertexAttribArray(normalLocation);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glBindVertexArray(0);
	}

	void Mesh::AddMeshGroup(const MeshGroup &meshGroup) {
		meshGroups.push_back(meshGroup);
	}

	std::string Mesh::getName() {
		return name;
	}
	
	void Mesh::Draw(const GLint projectionLocation, const GLint modelViewLocation, const Camera &camera, const glm::mat4 &modelView) {
		glBindVertexArray(vertexArrayObject);

		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera.getMVP()));
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelView));

		for (MeshGroup meshGroup : meshGroups) {
			glUniform3fv(ambientLocation, 1, glm::value_ptr(meshGroup.material->ambient));
			glUniform3fv(diffuseLocation, 1, glm::value_ptr(meshGroup.material->diffuse));
			glUniform1fv(opacityLocation, 1, &meshGroup.material->opacity);

			glDrawElements(GL_TRIANGLES, meshGroup.indexCount, GL_UNSIGNED_INT, reinterpret_cast<const GLint *>(meshGroup.indexOffset));
		}
		glBindVertexArray(0);
	}
}