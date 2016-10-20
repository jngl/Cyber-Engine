#include "System.hpp"
#include "Core/Error.hpp"

#include <iostream>

#include "Test1.hpp"

int main(int argc, char** argv){
    try{
        System::init(800, 600);
        
       /* if(argc!=2){
            std::cerr<<"Wrong number of arguments"<<std::endl;
            return 1;
        }*/
        
       // std::string testName = argv[1];
        
        //if(testName=="Test1"){
            test1();
        /*}else{
            std::cerr<<"Test not exist"<<std::endl;
        }*/
        
        System::destroy();
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
