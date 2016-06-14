#include "Camera.hpp"

namespace fruitjuice {
	Camera::Camera(const GLfloat fov, const GLfloat aspectRatio, const GLfloat near, const GLfloat far, const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) :
		fov(fov), aspectRatio(aspectRatio), near(near), far(far) {
		updateProjection();
		setLookat(eye, center, up);
	}

	Camera::Camera(const GLfloat fov, const GLfloat aspectRatio, const GLfloat near, const GLfloat far) : fov(fov), aspectRatio(aspectRatio), near(near), far(far) {
		updateProjection();
		setLookat(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	}

	Camera::Camera(const GLfloat fov, const GLfloat aspectRatio) : fov(fov), aspectRatio(aspectRatio), near(0.1f), far(100.0f) {
		updateProjection();
		setLookat(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	}

	Camera::Camera() : fov(glm::radians(45.0f)), aspectRatio(16.0f / 9.0f), near(0.1f), far(100.0f) {
	}

	Camera::~Camera() {
	}

	void Camera::setLookat(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
		modelView = glm::lookAt(eye, center, up);
	}

	void Camera::setFov(const GLfloat fov) {
		this->fov = fov;
		updateProjection();
	}

	void Camera::setAspectRatio(const GLfloat aspectRatio) {
		this->aspectRatio = aspectRatio;
		updateProjection();
	}

	void Camera::setNearFarPlane(const GLfloat near, const GLfloat far) {
		this->near = near;
		this->far = far;
		updateProjection();
	}

	GLfloat Camera::getFov() {
		return fov;
	}

	GLfloat Camera::getAspectRatio() {
		return aspectRatio;
	}

	GLfloat Camera::getNear() {
		return near;
	}

	GLfloat Camera::getFar() {
		return far;
	}

	void Camera::updateProjection() {
		projection = glm::perspective<GLfloat>(fov, aspectRatio, near, far);
	}
}