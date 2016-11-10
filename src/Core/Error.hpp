#ifndef GE_ERROR_HPP
#define GE_ERROR_HPP

#include <exception>
#include <string>

namespace core
{
    class Error : std::exception {
    public:
        Error () throw();
        Error (std::string message) throw();
        Error (const Error&) throw();
        Error& operator= (const Error&) throw();
        virtual ~Error() throw();
        
        virtual const char* what() const throw();
        
    private:
        std::string mMessage;
    };
}


#define coreAssert(cond) if(cond){throw core::Error("assert error line "+std::to_string(__LINE__)+" in file "+__FILE__);}
#define coreCheckParam(cond)  if(!(cond)){throw core::Error("wrong parameter line"+std::to_string(__LINE__)+" in file "+__FILE__);}
#define coreCheckPreCond(cond) if(cond){throw core::Error("wrong precondition line"+std::to_string(__LINE__)+" in file "+__FILE__);}
#define coreCHeckPostCond(cond) if(cond){throw core::Error("wrong postcondition line"+std::to_string(__LINE__)+" in file "+__FILE__);}

#endif
