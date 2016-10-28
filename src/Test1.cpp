#include "Test1.hpp"

#include "System.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/CubeData.hpp"

#include <iostream>
#include <cassert>
using namespace std;

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void test1(){ 
    Renderer::createRenderer();
    
    BasicCamera cam;
    cam.dist=5.f;
    
    Renderer::Mesh mesh;
    createMesh(&mesh,
               cubeVerticesSize,
               cubePos,
               cubeTexCoord,
               cubeNormal,
               cubeIndexSize,
               cubeIndex);
    
    
    Renderer::Shader shader;
    Renderer::createShader(shader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    
    Renderer::Texture tex;
    Renderer::createTexture(&tex, "../data/rocks_3_by_nobiax/diffuse.dds");
    
    glm::mat4 model(1.0f);
    
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f); 
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        updateBasicCamera(cam);
        
        glm::mat4 MVP = proj * cam.viewMatrix * model;
        
        Renderer::drawMesh(&mesh, MVP, shader);
        
        
        System::endFrame();
    }
    
    Renderer::destroyRenderer();
}
