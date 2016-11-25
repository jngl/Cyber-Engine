#include "System.hpp"
#include "Core/Error.hpp"

#include <iostream>

#include "Boxel.hpp"

int main(){
     try{
        boxel();
        return 0;
        
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
