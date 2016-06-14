#include <string>
#include <exception>

class invalid_format : public std::exception {
public:
	invalid_format();
	invalid_format(const std::string&);
	virtual ~invalid_format() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};
