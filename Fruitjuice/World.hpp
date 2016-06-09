#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

namespace fruitjuice {
	class World {
	public:
		World();
		~World();

		glm::mat4 getProjection() const { return projection; }
		glm::mat4 getModelView() const { return modelView; }
		glm::mat4 getMVP() const { return projection * modelView; }

		void translate(const glm::vec3 &vector);
		void rotate(const GLfloat amount, const glm::vec3 &axis);
	protected:
		glm::mat4 projection;
		glm::mat4 modelView;
	};
}