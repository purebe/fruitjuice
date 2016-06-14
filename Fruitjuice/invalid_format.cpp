#include "invalid_format.hpp"

invalid_format::invalid_format() : exception(), msg(nullptr) {
}

invalid_format::invalid_format(const std::string& m) : exception(), msg(m) {
}

invalid_format::~invalid_format() throw() {
}

const char* invalid_format::what() const throw() {
	return msg.c_str();
}
