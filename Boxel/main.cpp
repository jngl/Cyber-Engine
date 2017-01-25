#include "Core/Error.hpp"
#include "Core/Modules.hpp"

#include "System.hpp"

#include "Voxel.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/BasicCamera.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

#include <iostream>

extern "C"
int main(int argc, char *argv[]){
     try{
        Modules::constructAllModules();
    
        BasicCamera cam;
        Renderer::Camera_handle camHandle = Renderer::createCamera();
        Renderer::setActiveCamera(camHandle);
        cam.dist=30.f;
        
        VoxelChunk<10, 10, 10> chunk;
        chunk.loadTexture();
        chunk.generateGrid();
        chunk.generateMesh();
        
        Timer timer;
        float frameTime = 0.f;
        
        while(System::isRunning()){
            System::doEvent();
            System::clear();
        
            updateBasicCamera(cam, frameTime);
            Renderer::getCameraViewMatrixRef(camHandle) = cam.viewMatrix;
            
            chunk.draw();
            
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
