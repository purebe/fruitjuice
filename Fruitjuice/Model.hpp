#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "World.hpp"
#include "FileIO.hpp"
#include "Camera.hpp"

namespace fruitjuice {
	class Model : public World {
	public:
		Model();
		~Model();

		void LoadVertices(const std::vector<const GLfloat> vertices);
		void LoadNormals(const std::vector<const GLfloat> normals);
		void LoadIndices(const std::vector<const GLuint> indices);

		void SetMVPLocation(const GLint proj, const GLint mv) { projectionLocation = proj; modelViewLocation = mv; }
		void SetPositionLocation(const GLint position) { positionLocation = position; }
		void SetNormalLocation(const GLint normal) { normalLocation = normal; }

		void Draw(const Camera& camera) const;
	private:
		std::vector<const GLuint> buffers;
		std::vector<const GLuint> indices;
		std::vector<const GLfloat> vertices;
		std::vector<const GLfloat> normals;
		std::vector<const GLfloat> colors;

		GLuint indexBuffer;
		GLuint normalBuffer;
		GLuint vertexBuffer;

		GLint projectionLocation, modelViewLocation, positionLocation, normalLocation;
	};
}