#include "FilesSystem.hpp"
#include "../Core/Error.hpp"

#include <SDL.h>

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif


namespace FilesSystem{
	path getDataPath(){
		char* tmp = SDL_GetBasePath();
		
		if(!tmp){
				throw core::Error(std::string("Error getting data path: ") + SDL_GetError());
		}
		
		path dataPath(tmp);
		
		dataPath /="../data";
		
		if(!exists(dataPath) && is_directory(dataPath)){
			throw core::Error("data path not exist");
		}
		
		return dataPath;
	}

	path getPrefPath(){
		static std::string sPrefPath;
		char* tmp = SDL_GetPrefPath("jngl", "Cyber-Engine");
		
		if(!tmp){
			throw core::Error(std::string("Error getting pref path: ") + SDL_GetError());
		}
		
		path prefPath(tmp);
		
		if(!exists(prefPath) && is_directory(prefPath)){
			throw core::Error("pref path not exist");
		}
		
		return prefPath;
	}
}
