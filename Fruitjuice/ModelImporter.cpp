#include "ModelImporter.hpp"

namespace fruitjuice {
	void ModelImporter::Import(const std::string &path, const Shader &shader, Model &model) {
		offset = 0;
		std::string file = FileIO::readFile(path);
		std::istringstream fileStream(file);
		positionLocation = shader.GetAttribLocation("position");
		normalLocation = shader.GetAttribLocation("normal");
		ambientLocation = shader.GetUniformLocation("ambientColor");
		diffuseLocation = shader.GetUniformLocation("diffuseColor");
		opacityLocation = shader.GetUniformLocation("opacity");

		std::string materialLibrary = parseIdentifier("mtllib", fileStream);
		ImportMaterialLibrary("models/" + materialLibrary);

		std::vector<std::shared_ptr<Mesh>> meshes;
		while (true) {
			std::shared_ptr<Mesh> object = parseObject(fileStream);
			meshes.push_back(object);

			if (peekNextIdentifier(fileStream) != "o") {
				break;
			}
		}

		for (std::shared_ptr<Mesh> mesh : meshes) {
			model.AddMesh(mesh);
		}

		model.SetMVPLocation(shader.GetUniformLocation("projection"), shader.GetUniformLocation("modelView"));
	}

	std::vector<std::string> ModelImporter::ImportMaterialLibrary(const std::string &path) {
		std::string file = FileIO::readFile(path);
		std::istringstream fileStream(file);

		std::vector<std::string> materialNames;
		std::string material;
		do {
			material = ImportMaterial(fileStream);
			materialNames.push_back(material);
		} while (!material.empty());
		
		return materialNames;
	}

	std::string ModelImporter::ImportMaterial(std::istringstream &fileStream) {
		std::string materialName = parseIdentifier("newmtl", fileStream);
		if (!materialName.empty()) {
			std::string specularExponent = readNextLine(fileStream)[1];
			std::string opacity = readNextLine(fileStream)[1];
			std::string illuminationModel = readNextLine(fileStream)[1];
			std::vector<std::string> diffuseColor = readNextLine(fileStream);
			std::vector<std::string> ambientColor = readNextLine(fileStream);
			std::vector<std::string> specularColor = readNextLine(fileStream);
			std::vector<std::string> ke = readNextLine(fileStream);

			std::shared_ptr<Material> material = std::make_shared<Material>(materialName, lineToVec3(ambientColor), lineToVec3(diffuseColor), lineToVec3(specularColor), std::stof(specularExponent), std::stof(opacity), Material::parseLightingMode(illuminationModel));
			materialLibrary[materialName] = material;
		}

		return materialName;
	}

	glm::vec3 ModelImporter::lineToVec3(std::vector<std::string> vec) {
		glm::vec3 vector;
		if (vec.size() >= 4) {
			vector.r = std::stof(vec[1]);
			vector.g = std::stof(vec[2]);
			vector.b = std::stof(vec[3]);
		}

		return vector;
	}

	std::string ModelImporter::peekNextIdentifier(std::istringstream &fileStream) {
		std::vector<std::string> tokens = peekNextLine(fileStream);
		std::string identifier;
		if (tokens.size() > 0) {
			identifier = tokens[0];
		}

		return identifier;
	}

	std::vector<std::string> ModelImporter::peekNextLine(std::istringstream &fileStream) {
		std::streampos position = fileStream.tellg();
		std::vector<std::string> tokens = readNextLine(fileStream);
		fileStream.seekg(position);

		return tokens;
	}

	std::vector<std::string> ModelImporter::readNextLine(std::istringstream &fileStream) {
		std::string line, value;
		while (std::getline(fileStream, line)) {
			std::vector<std::string> words = StringHelper::Tokenize(line, ' ');
			if (words.size() <= 0) {
				continue;
			}
			else if (words[0][0] == '#') {
				continue;
			}

			return words;
		}

		// TODO: Throw unexpected read exception?
		return std::vector<std::string>();
	}

	std::vector<std::string> ModelImporter::readMatchingLines(std::string word, std::istringstream &fileStream) {
		std::streampos position = fileStream.tellg();
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(fileStream, line)) {
			std::vector<std::string> words = StringHelper::Tokenize(line, ' ');
			if (words.size() <= 0) {
				position = fileStream.tellg();
				continue;
			}
			if (words[0] == word) {
				position = fileStream.tellg();
				for (size_t itr = 1; itr < words.size(); ++itr) {
					lines.push_back(words[itr]);
				}
			}
			else if (words[0][0] == '#') {
				position = fileStream.tellg();
				continue;
			}
			else {
				fileStream.seekg(position);
				return lines;
			}
		}

		return lines;
	}

	std::string ModelImporter::parseIdentifier(std::string word, std::istringstream &fileStream) {
		std::vector<std::string> tokens = readNextLine(fileStream);

		if (tokens.size() > 0) {
			if (tokens[0] == word) {
				std::string value;
				for (size_t itr = 1; itr < tokens.size(); ++itr) {
					value.append(tokens[itr]);
				}
				return value;
			}
		}

		return "";
	}

	std::shared_ptr<Mesh> ModelImporter::parseObject(std::istringstream &fileStream) {
		std::string objectName = parseIdentifier("o", fileStream);
		std::vector<std::string> vertexData = readMatchingLines("v", fileStream);
		std::vector<std::string> normalData = readMatchingLines("vn", fileStream);

		std::vector<std::string> groupNameList, materialNameList, smoothShadingList;
		std::vector<std::vector<std::string>> faceDataList;
		while (true) {
			groupNameList.push_back(parseIdentifier("g", fileStream));
			materialNameList.push_back(parseIdentifier("usemtl", fileStream));
			smoothShadingList.push_back(parseIdentifier("s", fileStream));
			faceDataList.push_back(readMatchingLines("f", fileStream));

			if (peekNextIdentifier(fileStream) != "g") {
				break;
			}
		}

		// Build indices
		std::vector<MeshGroup> meshGroups;
		std::shared_ptr<Vertices> vertices = std::make_shared<Vertices>();
		std::shared_ptr<Indices> indices = std::make_shared<Indices>();
		std::shared_ptr<Normals> normals = std::make_shared<Normals>();
		GLuint indexId = 0, indexCount = 0, indexOffset = 0;
		std::map<const std::string, const GLuint> indexMap;

		// At this point, the first MeshGroup should have an index offset = 0
		for (const auto &faceData : faceDataList) {
			// At this point, 2nd iteration, the 2nd meshgroup should have an index offset = indexCount
			for (const std::string &face : faceData) {
				auto itr = indexMap.find(face);
				if (itr == indexMap.end()) {
					std::vector<std::string> tokens = StringHelper::Tokenize(face, '/');

					vertices->push_back(std::stof(vertexData[((std::stoul(tokens[0]) - (1 + offset)) * 3) + 0]));
					vertices->push_back(std::stof(vertexData[((std::stoul(tokens[0]) - (1 + offset)) * 3) + 1]));
					vertices->push_back(std::stof(vertexData[((std::stoul(tokens[0]) - (1 + offset)) * 3) + 2]));
					normals->push_back(std::stof(normalData[((std::stoul(tokens[2]) - (1 + offset)) * 3) + 0]));
					normals->push_back(std::stof(normalData[((std::stoul(tokens[2]) - (1 + offset)) * 3) + 1]));
					normals->push_back(std::stof(normalData[((std::stoul(tokens[2]) - (1 + offset)) * 3) + 2]));

					indices->push_back(indexId);
					indexMap.insert(std::pair<const std::string, const GLuint>(face, indexId));
					indexId++;
				}
				else {
					indices->push_back((*itr).second);
				}
				++indexCount;
			}

			MeshGroup meshGroup(indexOffset, indexCount);
			indexOffset += indexCount;
			meshGroups.push_back(meshGroup);
		}
		offset += indexId;

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(objectName, vertices, normals, indices, positionLocation, normalLocation, ambientLocation, diffuseLocation, opacityLocation);
		for (size_t itr = 0; itr < groupNameList.size(); ++itr) {
			meshGroups[itr].name = groupNameList[itr];
			meshGroups[itr].material = materialLibrary[materialNameList[itr]];

			mesh->AddMeshGroup(meshGroups[itr]);
		}

		return mesh;
	}
}