#include "CyberEngine/filesystem.hpp"

#include <CyberBase.hpp>

#include <SDL.h>

namespace ce
{
    std::string getBaseDirectory(){
        return SDL_GetBasePath();
    }
  
    std::string getGameDirectory(){
        return "data";
    }

  
    std::string getPathSeparator(){
#ifdef _WIN32
        return "\\";
#else
        return "/";
#endif
    }
}
