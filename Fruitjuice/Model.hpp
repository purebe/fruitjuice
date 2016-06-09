#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "FileIO.hpp"
#include "Camera.hpp"

namespace fruitjuice {
	class Model {
	public:
		Model();
		Model(const std::string &path);
		~Model();

		void Import(const std::string &path);

		void LoadVertexData(const std::vector<const GLfloat> vertices);
		void LoadIndexData(const std::vector<const GLuint> indices);

		void SetMVPLocation(GLint proj, GLint mv) { projectionLocation = proj; modelViewLocation = mv; }
		void SetPositionLocation(GLint position) { positionLocation = position; }

		void Draw(Camera& camera) const;

		void translate(const glm::vec3 &vector);
		void rotate(const GLfloat amount, const glm::vec3 &axis);
	private:
		std::vector<const GLuint> buffers;
		std::vector<const GLuint> indices;
		std::vector<const GLfloat> vertices;
		std::vector<const GLfloat> colors;

		glm::mat4 modelView;

		GLuint indexBuffer;
		GLuint vertexBuffer;

		GLint projectionLocation, modelViewLocation, positionLocation;
	};
}