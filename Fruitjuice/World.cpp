#include "World.hpp"

namespace fruitjuice {
	World::World() : projection(1.0f), modelView(1.0f) {
	}

	World::~World() {
	}

	void World::translate(const glm::vec3 &vector) {
		modelView = glm::translate(modelView, vector);
	}

	void World::rotate(const GLfloat amount, const glm::vec3 &axis) {
		modelView = glm::rotate(modelView, amount, axis);
	}
}