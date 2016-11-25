#include "Modules.hpp"

#include "System.hpp"
#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"

namespace Modules
{
    void constructAllModules(){
        System::constructSystem(800, 600);
        GraphicsWrapper::constructGraphicsWrapper();
    }
    
    void destructAllModules(){
        GraphicsWrapper::destructGraphicsWrapper();
        System::destructSystem();
    }
}
