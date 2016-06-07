#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

namespace fruitjuice {
	class Camera {
	public:
		Camera(const GLfloat fov, const GLfloat aspectRatio);
		~Camera();

		glm::mat4 getCamera();

		void translate(glm::vec3 vector);

	private:
		glm::mat4 projection;
		glm::mat4 modelView;
	};
}