#include "Core/Error.hpp"
#include "Core/Modules.hpp"

#include "System.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

#include "BoxelScene/BoxelScene.hpp"

#include <iostream>

extern "C"
int main(int argc, char *argv[]){
     try{
        Modules::constructAllModules();
	
	BoxelScene mScene;
        
        Timer timer;
        float frameTime = 0.f;
        
        while(System::isRunning()){
            System::doEvent();
            System::clear();
	    
	    mScene.update(frameTime);
	    
	    mScene.draw();
            
            System::endFrame();
            
            frameTime = timer.timeInSecond();
            timer.restart();
        }
        Modules::destructAllModules();
    
        return 0;
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
