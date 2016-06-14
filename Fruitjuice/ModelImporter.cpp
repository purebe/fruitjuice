#include "ModelImporter.hpp"

namespace fruitjuice {
	void ModelImporter::Import(const std::string &path, const Shader &shader, Model &model) {
		offset = 0;
		std::string file = FileIO::readFile(path);
		std::istringstream fileStream(file);

		std::string materialLibrary = parseIdentifier("mtllib", fileStream);
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

		model.SetPositionLocation(shader.GetAttribLocation("position"));
		model.SetNormalLocation(shader.GetAttribLocation("normal"));
		model.SetMVPLocation(shader.GetUniformLocation("projection"), shader.GetUniformLocation("modelView"));
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
		GLuint indexId = 0, indexCount = 0, indexStart = 0;
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

			MeshGroup meshGroup(indexStart, indexCount);
			indexStart += indexCount;
			meshGroups.push_back(meshGroup);
		}
		offset += indexId;

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(objectName, vertices, normals, indices);
		for (size_t itr = 0; itr < groupNameList.size(); ++itr) {
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->name = materialNameList[itr];

			meshGroups[itr].name = groupNameList[itr];
			meshGroups[itr].material = material;

			mesh->AddMeshGroup(meshGroups[itr]);
		}

		return mesh;
	}
}