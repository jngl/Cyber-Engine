#include "Test1.hpp"

#include <iostream>

#include <GL/glew.h>

#include "System.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/MeshData.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/GLDebug.hpp"

#include "Math/Angle3.hpp"

void test1(){
    Renderer::createRenderer();
    
    BasicCamera cam;
    cam.dist=5.f;
    
    MeshData data;
    data.makeCube();
    Renderer::Mesh mesh;
    createMesh(&mesh,
               data.vertices.size(),
               &(data.vertices[0].x),
               data.elements.size(),
               data.elements.data());
    
    
    Renderer::Shader shader;
    Renderer::createShader(shader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    
    math::Matrix4f model;
    
    math::Matrix4f proj;
    proj.setPerspective(45.f, 4.f/3.f, 0.01f, 10000.f);
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        updateBasicCamera(cam);
        
        math::Matrix4f MVP = proj * cam.viewMatrix * model;
        
        Renderer::drawMesh(&mesh, MVP, shader);
        
        
        System::endFrame();
    }
    
    Renderer::destroyRenderer();
}
