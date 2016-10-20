#include "Test1.hpp"

#include <iostream>

#include <glad/glad.h>

#include "System.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/MeshData.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/GLDebug.hpp"
#include "Renderer/CubeData.hpp"

#include "Math/Angle3.hpp"
#include "Math/Vector3.hpp"

void test1(){
    Renderer::createRenderer();
    
    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    
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
