#include "Mesh.hpp"

namespace fruitjuice {
	Mesh::Mesh(std::string name, std::shared_ptr<Vertices> vertices, std::shared_ptr<Normals> normals, std::shared_ptr<Indices> indices) :
		name(name), vertices(vertices), normals(normals), indices(indices) {
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices->size() * sizeof(GLfloat), &(*vertices)[0], GL_STATIC_DRAW);

		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals->size() * sizeof(GLfloat), &(*normals)[0], GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices->size() * sizeof(GLuint), &(*indices)[0], GL_STATIC_DRAW);
	}

	void Mesh::AddMeshGroup(const MeshGroup &meshGroup) {
		meshGroups.push_back(meshGroup);
	}


	std::string Mesh::getName() {
		return name;
	}
	
	void Mesh::Draw(GLuint positionLocation, GLuint normalLocation) {
		glEnableVertexAttribArray(positionLocation);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(normalLocation);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		for (MeshGroup meshGroup : meshGroups) {
			glDrawElements(GL_TRIANGLES, meshGroup.indexCount, GL_UNSIGNED_INT, (const void *)meshGroup.indexStart);
			//glDrawElements(GL_TRIANGLES, meshGroup.indexCount, GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(positionLocation);
		glDisableVertexAttribArray(normalLocation);
	}
}