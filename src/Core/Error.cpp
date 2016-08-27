#include "Error.hpp"

namespace core
{
    Error::Error () throw():
        mMessage("unknown error"){
    }

    Error::Error (std::string message) throw():
        mMessage(message){
    }

    Error::Error (const Error& error) throw():
        mMessage(error.mMessage){
        
    }

    Error& Error::operator= (const Error& error) throw(){
        mMessage = error.mMessage;
    }

    Error::~Error() throw(){
    }

    const char* Error::what() const throw(){
        return mMessage.c_str();
    }
}
