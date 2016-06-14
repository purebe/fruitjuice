#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace fruitjuice {
	class StringHelper {
	public:
		static std::vector<std::string> Tokenize(const std::string &str, const char delim) {
			std::vector<std::string> tokens;

			std::stringstream stream(str);
			std::string token;
			while (std::getline(stream, token, delim)) {
				tokens.push_back(std::move(token));
			}

			return tokens;
		}
	};
}