#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "World.hpp"

namespace fruitjuice {
	class Camera : public World {
	public:
		Camera(const GLfloat fov, const GLfloat aspectRatio);
		~Camera();
	private:
	};
}