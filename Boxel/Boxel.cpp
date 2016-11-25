
#include "Boxel.hpp"

#include "System.hpp"

#include "Voxel.hpp"

#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/CubeData.hpp"

#include <iostream>
#include <cassert>
using namespace std;

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

void boxel(){ 
    GraphicsWrapper::constructGraphicsWrapper();
    
    BasicCamera cam;
    cam.dist=20.f;
    
    VoxelChunk<10, 10, 10> chunk;
    chunk.generateGrid();
    chunk.generateMesh();
    chunk.loadTexture();
    
    
    GraphicsWrapper::Shader shader;
    GraphicsWrapper::createShader(shader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    
    glm::mat4 model(1.0f);
    
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f); 
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        updateBasicCamera(cam);
        
       model = glm::translate(glm::mat4(1.0f), glm::vec3(-5, -5, -5));
        
        glm::mat4 MVP = proj * cam.viewMatrix * model;
        
        chunk.draw(MVP, shader);
        
        System::endFrame();
    }
    GraphicsWrapper::destructGraphicsWrapper();
}
