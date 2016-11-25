#include "System.hpp"
#include "Core/Error.hpp"

#include <iostream>

#include "Boxel.hpp"

int main(){
     try{
        System::init(800, 600);
        
        boxel();
        
        System::destroy();
        return 0;
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
