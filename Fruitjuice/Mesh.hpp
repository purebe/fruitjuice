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

namespace fruitjuice {
	struct MeshGroup {
		MeshGroup(GLuint indexStart, GLuint indexCount, std::string name, std::shared_ptr<Material> material) :
			indexStart(indexStart), indexCount(indexCount), name(name), material(material) { }
		MeshGroup(GLuint indexStart, GLuint indexCount) : indexStart(indexStart), indexCount(indexCount) { }
		MeshGroup() { }

		std::string name;
		std::shared_ptr<Material> material;
		GLuint indexStart, indexCount;
	};

	class Mesh {
	public:
		Mesh(std::string name, std::shared_ptr<Vertices> vertices, std::shared_ptr<Normals> normals, std::shared_ptr<Indices> indices);

		void AddMeshGroup(const MeshGroup &meshGroup);
		void Draw(GLuint positionLocation, GLuint normalLocation);

		std::string getName();
	private:
		GLuint vertexBuffer, normalBuffer, indexBuffer;
		std::shared_ptr<Vertices> vertices;
		std::shared_ptr<Normals> normals;
		std::shared_ptr<Indices> indices;
		std::vector<MeshGroup> meshGroups;
		std::string name;
	};
}