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
		for (const auto &kv : meshes) {
			kv.second->Draw(projectionLocation, modelViewLocation, camera, modelView);
		}
	}
}