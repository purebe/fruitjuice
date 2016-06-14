#include "Model.hpp"

namespace fruitjuice {
	Model::Model() {
	}
	
	Model::~Model() {
	}

	void Model::AddMesh(std::shared_ptr<Mesh> mesh) {
		std::string id = mesh->getName();
		meshes[id] = mesh;
	}

	void Model::Draw(const Camera& camera) const {
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera.getMVP()));
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelView));

		for (const auto &kv : meshes) {
			kv.second->Draw(positionLocation, normalLocation);
		}
	}
}