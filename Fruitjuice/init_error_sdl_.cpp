#include "init_error_sdl.hpp"

init_error_sdl::init_error_sdl() : init_error(), msg(SDL_GetError()) {
}

init_error_sdl::init_error_sdl(const std::string& m) : init_error(), msg(m) {
}

init_error_sdl::~init_error_sdl() throw() {
}

const char* init_error_sdl::what() const throw() {
	return msg.c_str();
}
