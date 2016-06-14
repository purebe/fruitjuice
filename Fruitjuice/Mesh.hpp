#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "OpenGLTypes.hpp"
#include "Material.hpp"
#include "Camera.hpp"

namespace fruitjuice {
	struct MeshGroup {
		MeshGroup(GLuint indexOffset, GLuint indexCount, std::string name, std::shared_ptr<Material> material) :
			indexOffset(indexOffset), indexCount(indexCount), name(name), material(material) { }
		MeshGroup(GLuint indexOffset, GLuint indexCount) : indexOffset(indexOffset), indexCount(indexCount) { }
		MeshGroup() { }

		std::string name;
		std::shared_ptr<Material> material;
		GLint indexOffset;
		GLsizei indexCount;
	};

	class Mesh {
	public:
		Mesh(std::string name, std::shared_ptr<Vertices> vertices, std::shared_ptr<Normals> normals, std::shared_ptr<Indices> indices,
			GLuint positionLocation, GLuint normalLocation, GLuint ambientLocation, GLuint diffuseLocation, GLuint opacityLocation);

		void AddMeshGroup(const MeshGroup &meshGroup);
		void Draw(const GLint projectionLocation, const GLint modelViewLocation, const Camera &camera, const glm::mat4 &modelView);

		std::string getName();
	private:
		GLuint vertexArrayObject, vertexBuffer, normalBuffer, indexBuffer;
		std::shared_ptr<Vertices> vertices;
		std::shared_ptr<Normals> normals;
		std::shared_ptr<Indices> indices;
		std::vector<MeshGroup> meshGroups;
		std::string name;

		GLuint ambientLocation, diffuseLocation, opacityLocation;
	};
}