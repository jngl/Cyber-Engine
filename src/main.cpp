#include "System.hpp"
#include "SceneBase.hpp"
#include "Core/Error.hpp"
#include "SceneTest2.hpp"

#include <iostream>

#include "Test1.hpp"
#include "Montagne.hpp"


void test2(){    
    SceneTest2 scene;
            
    while(System::isRunning()){
        System::doEvent();
        System::clear();
        
        scene.update();
        scene.render();
        
        System::endFrame();
    }
    
    std::cout<<"test2"<<std::endl;
}

int main(int argc, char** argv){
    try{
        System::init(800, 600);
        
        if(argc!=2){
            std::cerr<<"Wrong number of arguments"<<std::endl;
            return 1;
        }
        
        std::string testName = argv[1];
        
        if(testName=="Test1"){
            test1();
        }else if(testName=="Test2"){
            test2();
        }else if(testName=="Montagne"){
            montagne();
        }else{
            std::cerr<<"Test not exist"<<std::endl;
        }
        
        System::destroy();
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
