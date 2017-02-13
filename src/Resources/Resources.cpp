#include "Resources.hpp"

#include "PlatformIndependenceLayer/FilesSystem.hpp"

#include <iostream>

namespace Resources{
	void createResources(){
		std::cout<<"Data path : "<<FilesSystem::getDataPath()<<std::endl;
		std::cout<<"Pref path : "<<FilesSystem::getPrefPath()<<std::endl;
	}
	
    void destroyResources(){
	}
};
