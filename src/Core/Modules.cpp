#include "Modules.hpp"

#include "System.hpp"
#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"
#include "Renderer/Renderer.hpp"
#include "Resources/Resources.hpp"

namespace Modules
{
    void constructAllModules(){
		Resources::createResources();
        System::constructSystem(800, 600);
        GraphicsWrapper::constructGraphicsWrapper();
        Renderer::createRenderer();
    }
    
    void destructAllModules(){
        Renderer::destroyRenderer();
        GraphicsWrapper::destructGraphicsWrapper();
        System::destructSystem();
		Resources::destroyResources();
    }
}
