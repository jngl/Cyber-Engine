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
    
    
    Renderer::ShaderId shader;
    Renderer::createShader(shader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    glCheck(glUseProgram(shader));
    GLuint GBuffersMdvMatLoc = glGetUniformLocation(shader,"MVP");
    GLuint GBuffersVertexLoc = glGetAttribLocation(shader,"position");
    glCheckError(__FILE__, __LINE__);
    
    math::Matrix4f model;
    
    math::Matrix4f proj;
    proj.setPerspective(45.f, 4.f/3.f, 0.01f, 10000.f);
    Renderer::setProjectionMatrix(proj);
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        updateBasicCamera(cam);
        
        math::Matrix4f MVP = proj * Renderer::currentViewMatrix * model;
        
        glCheck(glUseProgram(shader));
        glCheck(glUniformMatrix4fv(GBuffersMdvMatLoc,1,GL_FALSE,&MVP[0]));
        
        
        //Renderer::drawMesh(&mesh, model);
        
        
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,mesh.id[0]));
        glCheck(glEnableVertexAttribArray(GBuffersVertexLoc));
        glCheck(glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0));

        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh.id[1]));
        glCheck(glDrawElements(GL_TRIANGLES,
                       mesh.nbFaces,
                       GL_UNSIGNED_INT,
                       (void *)0));

        glCheck(glBindFramebuffer(GL_FRAMEBUFFER,0));
        
        
        System::endFrame();
    }
    
    Renderer::destroyRenderer();
}
