#include "System.hpp"
#include "Core/Error.hpp"

#include <iostream>

#include <SDL.h>

#include "Boxel.hpp"

#if defined(SDL_MAIN_NEEDED) || defined(SDL_MAIN_AVAILABLE)
int SDL_main(int argc, char *argv[]){
#else
int main(){
#endif
     try{
        boxel();
        return 0;
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
