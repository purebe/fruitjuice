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
		Model(const std::string &path);
		~Model();

		void Import(const std::string &path);

		void LoadVertexData(const std::vector<const GLfloat> vertices);
		void LoadIndexData(const std::vector<const GLuint> indices);

		void SetMVPLocation(const GLint proj, const GLint mv) { projectionLocation = proj; modelViewLocation = mv; }
		void SetPositionLocation(const GLint position) { positionLocation = position; }

		void Draw(const Camera& camera) const;
	private:
		std::vector<const GLuint> buffers;
		std::vector<const GLuint> indices;
		std::vector<const GLfloat> vertices;
		std::vector<const GLfloat> colors;

		GLuint indexBuffer;
		GLuint vertexBuffer;

		GLint projectionLocation, modelViewLocation, positionLocation;
	};
}