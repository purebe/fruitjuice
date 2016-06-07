#include <string>
#include "init_error.hpp"
#include <SDL.h>

class init_error_sdl : public init_error {
public:
	init_error_sdl();
	init_error_sdl(const std::string&);
	virtual ~init_error_sdl() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};
