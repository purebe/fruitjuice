#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <GL\glew.h>
#include <glm.hpp>

#include "Shader.hpp"
#include "Model.hpp"
#include "FileIO.hpp"
#include "StringHelper.hpp"

namespace fruitjuice {
	namespace ModelImporter {
		static Model Import(const std::string &path, const Shader &shader) {
			std::vector<const GLfloat> obj_vertices;
			std::vector<const GLfloat> obj_normals;
			std::vector<const std::string> obj_faces;
			std::map<const std::string, const GLuint> indexMap;

			std::string file = FileIO::readFile(path);
			std::istringstream fileStream(file);
			std::string line, word;
			while (std::getline(fileStream, line)) {
				std::vector<std::string> words = StringHelper::Tokenize(line, ' ');
				if (words.size() <= 0) {
					continue;
				}

				if (words[0] == "v") {
					for (auto itr = words.begin() + 1; itr != words.end(); ++itr) {
						obj_vertices.push_back(std::stof(*itr));
					}
				} else if (words[0] == "vn") {
					for (auto itr = words.begin() + 1; itr != words.end(); ++itr) {
						obj_normals.push_back(std::stof(*itr));
					}
				} else if (words[0] == "f") {
					obj_faces.push_back(words[1]);
					obj_faces.push_back(words[2]);
					obj_faces.push_back(words[3]);
				}
			}

			GLuint indexCounter = 0;
			std::vector<const GLuint> indices;
			std::vector<const GLfloat> vertices, normals;
			for (const std::string &face : obj_faces) {
				auto itr = indexMap.find(face);
				if (itr == indexMap.end()) {
					std::vector<std::string> tokens = StringHelper::Tokenize(face, '/');
					vertices.push_back(obj_vertices[((std::stoul(tokens[0]) - 1) * 3) + 0]);
					vertices.push_back(obj_vertices[((std::stoul(tokens[0]) - 1) * 3) + 1]);
					vertices.push_back(obj_vertices[((std::stoul(tokens[0]) - 1) * 3) + 2]);
					normals.push_back(obj_normals[((std::stoul(tokens[2]) - 1) * 3) + 0]);
					normals.push_back(obj_normals[((std::stoul(tokens[2]) - 1) * 3) + 1]);
					normals.push_back(obj_normals[((std::stoul(tokens[2]) - 1) * 3) + 2]);

					indices.push_back(indexCounter);
					indexMap.insert(std::pair<const std::string, const GLuint>(face, indexCounter));
					indexCounter++;

				} else {
					indices.push_back((*itr).second);
				}
			}

			Model model;
			model.LoadVertices(vertices);
			model.LoadNormals(normals);
			model.LoadIndices(indices);
			model.SetPositionLocation(shader.GetAttribLocation("position"));
			model.SetNormalLocation(shader.GetAttribLocation("normal"));
			model.SetMVPLocation(shader.GetUniformLocation("projection"), shader.GetUniformLocation("modelView"));

			return model;
		}
	}
}