#include "FilesSystem.hpp"
#include "Error.hpp"

#include <SDL.h>

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

std::string FilesSystem::getDataPath(){
    static std::string sDataPath;
    if(sDataPath.empty()){
        char *basePath = SDL_GetBasePath();
        
        if(!basePath){
            throw core::Error(std::string("Error getting data path: ") + SDL_GetError());
        }
        
        sDataPath = basePath;
        SDL_free(basePath);
        
        sDataPath = sDataPath + "data" + PATH_SEP;
    }
    return sDataPath;
}

std::string FilesSystem::getPrefPath(){
    static std::string sPrefPath;
    if(sPrefPath.empty()){
        char *prefPath = SDL_GetPrefPath("jngl", "GameEngine");
        
        if(!prefPath){
            throw core::Error(std::string("Error getting pref path: ") + SDL_GetError());
        }
        
        sPrefPath = prefPath;
        SDL_free(prefPath);
    }
    return sPrefPath;
}
