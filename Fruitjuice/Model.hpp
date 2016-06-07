#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Camera.hpp"

namespace fruitjuice {
	class Model {
	public:
		Model();
		~Model();

		void LoadVertexData(const std::vector<const GLfloat> vertices);
		void LoadIndexData(const std::vector<const GLuint> indices);

		void SetMVPLocation(GLint proj, GLint mv) { projectionLocation = proj; modelViewLocation = mv; }
		void SetPositionLocation(GLint position) { positionLocation = position; }

		void Tick();
		void Draw(Camera& camera) const;
	private:
		std::vector<const GLuint> buffers;
		std::vector<const GLfloat> vertices;
		std::vector<const GLuint> indices;

		glm::mat4 modelView;

		GLfloat rotation = 45.0f;

		GLuint indexBuffer;
		GLuint vertexBuffer;

		GLint projectionLocation, modelViewLocation, positionLocation;
	};
}