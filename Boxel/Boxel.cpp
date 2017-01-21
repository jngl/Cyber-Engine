
#include "Boxel.hpp"

#include "System.hpp"

#include "Voxel.hpp"

#include "Renderer/Renderer.hpp"
#include "PlatformIndependenceLayer/Timer.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/CubeData.hpp"
#include "Core/Modules.hpp"

#include <iostream>
#include <cassert>
using namespace std;

void boxel(){ 
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
}
