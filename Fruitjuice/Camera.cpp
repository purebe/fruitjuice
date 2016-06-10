#include "Camera.hpp"

namespace fruitjuice {
	Camera::Camera(const GLfloat fov, const GLfloat aspectRatio) {
		projection = glm::perspective<GLfloat>(fov, aspectRatio, 1.0f, -1.0f);
		modelView = glm::mat4();
	}

	Camera::~Camera() {
	}
}