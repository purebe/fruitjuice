#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "World.hpp"

namespace fruitjuice {
	class Camera : public World {
	public:
		Camera(const GLfloat fov, const GLfloat aspectRatio, const GLfloat near, const GLfloat far, const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
		Camera(const GLfloat fov, const GLfloat aspectRatio, const GLfloat near, const GLfloat far);
		Camera(const GLfloat fov, const GLfloat aspectRatio);
		Camera();

		~Camera();

		void setLookat(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
		void setFov(const GLfloat fov);
		void setAspectRatio(const GLfloat aspectRatio);
		void setNearFarPlane(const GLfloat near, const GLfloat far);

		GLfloat getFov();
		GLfloat getAspectRatio();
		GLfloat getNear();
		GLfloat getFar();
	private:
		GLfloat fov, aspectRatio, near, far;

		void updateProjection();
	};
}