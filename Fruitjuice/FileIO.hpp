#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>

namespace fruitjuice {
	class FileIO {
	public:
		static std::string getCurrentWorkingDirectory() _NOEXCEPT {
			char cwd[512];
			_getcwd(cwd, 512);

			return std::string(cwd);
		}

		static std::string readFile(const std::string &path) {
			std::string fullpath(FileIO::getCurrentWorkingDirectory() + "/" + path);

			std::ifstream srcFile(fullpath);
			srcFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);

			std::stringstream buffer;
			buffer << srcFile.rdbuf();

			return buffer.str();
		}
	};
}