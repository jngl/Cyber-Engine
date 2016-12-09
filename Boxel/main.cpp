#include "System.hpp"
#include "Core/Error.hpp"

#include <iostream>

#include <SDL_main.h>

#include "Boxel.hpp"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[]){
     try{
        boxel();
        return 0;
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
