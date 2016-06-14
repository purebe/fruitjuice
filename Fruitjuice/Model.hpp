#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "OpenGLTypes.hpp"
#include "World.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "FileIO.hpp"
#include "Camera.hpp"

namespace fruitjuice {
	class Model : public World {
	public:
		Model();
		~Model();

		void AddMesh(std::shared_ptr<Mesh> mesh);

		void SetMVPLocation(const GLint proj, const GLint mv) { projectionLocation = proj; modelViewLocation = mv; }

		void Draw(const Camera& camera) const;
	private:
		std::map<const std::string, std::shared_ptr<Mesh>> meshes;

		GLint projectionLocation, modelViewLocation;
	};
}