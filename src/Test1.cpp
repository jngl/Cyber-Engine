#include "Test1.hpp"

#include <iostream>

#include "System.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/MeshData.hpp"

#include "Math/Angle3.hpp"

struct Camera
{
    float dist;
    math::Angle3f angle;
};

void setView2(Camera& camera){
    math::Matrix4f view;
    math::Vec3f dir = camera.angle.toDirection();
    math::Vec3f pos = dir*camera.dist;
    math::Vec3f up(0.f, 1.f, 0.f);
    math::Vec3f zero(0.f, 0.f, 0.f);
    
    if(System::keyIsPressed(System::Key::KEY_z)){
        camera.dist -= 0.001;
    }else if(System::keyIsPressed(System::Key::KEY_s)){
        camera.dist += 0.001f;
    }else if(System::keyIsPressed(System::Key::KEY_RIGHT)){
        camera.angle.yaw.rotateRadian(0.0001f);
    }else if(System::keyIsPressed(System::Key::KEY_LEFT)){
        camera.angle.yaw.rotateRadian(-0.0001f);
    }else if(System::keyIsPressed(System::Key::KEY_UP)){
        camera.angle.pitch.rotateRadian(0.0001f);
    }else if(System::keyIsPressed(System::Key::KEY_DOWN)){
        camera.angle.pitch.rotateRadian(-0.0001f);
    }
    
    view.lookAt(pos, zero, up);
    Renderer::setViewMatrix(view);
}

void test1(){
    Renderer::createRenderer();
    
    Camera cam;
    cam.dist=5.f;
    
    MeshData data;
    data.makeCube();
    Renderer::Mesh mesh;
    createMesh(&mesh,
               data.vertices.size(),
               &(data.vertices[0].x),
               data.elements.size(),
               data.elements.data());
    
    math::Matrix4f model;
    
    math::Matrix4f proj;
    proj.setPerspective(45.f, 4.f/3.f, 0.01f, 10000.f);
    Renderer::setProjectionMatrix(proj);
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        setView2(cam);
        
        Renderer::drawMesh(&mesh, model);
        
        System::endFrame();
    }
    
    Renderer::destroyRenderer();
}
