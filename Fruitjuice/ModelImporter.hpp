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
	private:
		GLuint offset = 0;
		std::string peekNextIdentifier(std::istringstream &fileStream);
		std::vector<std::string> peekNextLine(std::istringstream &fileStream);
		std::vector<std::string> readNextLine(std::istringstream &fileStream);
		std::vector<std::string> readMatchingLines(std::string word, std::istringstream &fileStream);
		std::string parseIdentifier(std::string word, std::istringstream &fileStream);
		std::shared_ptr<Mesh> parseObject(std::istringstream &fileStream);
	};
}