#include "Modules.hpp"

#include "System.hpp"
#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"
#include "Renderer/Renderer.hpp"

namespace Modules
{
    void constructAllModules(){
        System::constructSystem(800, 600);
        GraphicsWrapper::constructGraphicsWrapper();
        Renderer::createRenderer();
    }
    
    void destructAllModules(){
        Renderer::destroyRenderer();
        GraphicsWrapper::destructGraphicsWrapper();
        System::destructSystem();
    }
}
