#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <GL\glew.h>
#include <glm.hpp>

#include "invalid_format.hpp"
#include "OpenGLTypes.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "FileIO.hpp"
#include "StringHelper.hpp"

namespace fruitjuice {
	class ModelImporter {
	public:
		void Import(const std::string &path, const Shader &shader, Model &model);
		std::vector<std::string> ImportMaterialLibrary(const std::string &path);
		std::string ImportMaterial(std::istringstream &fileStream);
	private:
		GLuint offset = 0;
		GLint positionLocation, normalLocation, ambientLocation, diffuseLocation, opacityLocation;
		std::map<const std::string, std::shared_ptr<Material>> materialLibrary;

		std::string peekNextIdentifier(std::istringstream &fileStream);
		std::vector<std::string> peekNextLine(std::istringstream &fileStream);
		std::vector<std::string> readNextLine(std::istringstream &fileStream);
		std::vector<std::string> readMatchingLines(std::string word, std::istringstream &fileStream);
		std::string parseIdentifier(std::string word, std::istringstream &fileStream);
		glm::vec3 lineToVec3(std::vector<std::string> vec);
		std::shared_ptr<Mesh> parseObject(std::istringstream &fileStream);
	};
}