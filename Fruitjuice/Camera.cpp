#include "Camera.hpp"

namespace fruitjuice {
	Camera::Camera(const GLfloat fov, const GLfloat aspectRatio) {
		projection = glm::perspective<GLfloat>(fov, aspectRatio, 1.0f, -1.0f);
		modelView = glm::mat4(1.0f);
	}

	Camera::~Camera() {
	}

	glm::mat4 Camera::getCamera() {
		return projection * modelView;
	}

	void Camera::translate(glm::vec3 vector) {
		modelView = glm::translate(modelView, vector);
	}
}