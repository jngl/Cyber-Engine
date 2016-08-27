#include "System.hpp"
#include "SceneBase.hpp"
#include "Core/Error.hpp"

int main(int argc, char** argv){
    try{
        System::init(800, 600);
        
        if(argc!=2){
            std::cerr<<"Wrong number of arguments"<<std::endl;
            return 1;
        }
        
        SceneBase* scene = Scene::createScene(argv[1]);
            
        while(System::isRunning()){
            System::doEvent();
            System::clear();
            
            scene->update();
            scene->render();
            
            System::endFrame();
        }
        
        Scene::destroyScene(scene);
        System::destroy();
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
