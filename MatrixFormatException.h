#include<exception>
#include<stdexcept>

class MatrixFormatException : public std::runtime_error
{
	
	public:
		MatrixFormatException() : std::runtime_error("Einzulesende Matrix hat falsches Format" )
		{};
	
		virtual char const * what() const throw() { return std::runtime_error::what();}
};

