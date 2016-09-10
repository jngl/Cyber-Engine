#include "BasicCamera.hpp"

#include "../System.hpp"

#include "../Math/Matrix4.hpp"

#include "Renderer.hpp"

void updateBasicCamera(BasicCamera& camera){
    
    math::Vec3f pos = camera.angle.toDirection() * camera.dist;
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
    
    camera.viewMatrix.setIdentity();
    camera.viewMatrix.lookAt(pos, zero, up);
}
