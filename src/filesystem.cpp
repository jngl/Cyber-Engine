#include "CyberEngine/filesystem.hpp"

#include <CyberBase.hpp>

#include <SDL.h>

namespace filesystem
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

  // main
  void createFileSystem(){
    CB_LOG_INFO<<"FileSystem construct";
    CB_LOG_INFO<<"Data Directory : \"" << getBaseDirectory() << getGameDirectory() << "\"";
  }
  
  void destroyFileSystem(){
    CB_LOG_INFO<<"FileSystem destruct";
  }

}
