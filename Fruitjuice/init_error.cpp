#include "init_error.hpp"

init_error::init_error() : exception(), msg(nullptr) {
}

init_error::init_error(const std::string& m) : exception(), msg(m) {
}

init_error::~init_error() throw() {
}

const char* init_error::what() const throw() {
	return msg.c_str();
}