#include <string>
#include <exception>

class init_error : public std::exception {
public:
	init_error();
	init_error(const std::string&);
	virtual ~init_error() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};