#include "BasicCamera.hpp"

#include "../System.hpp"

#include "../Math/Matrix4.hpp"

#include "Renderer.hpp"

void updateBasicCamera(BasicCamera& camera){
    
    math::Vec3f pos = camera.angle.toDirection() * camera.dist;
    math::Vec3f up(0.f, 1.f, 0.f);
    math::Vec3f zero(0.f, 0.f, 0.f);
    
    const float speed = 0.0001f;
    
    if(System::keyIsPressed(System::Key::KEY_z)){
        camera.dist -= speed;
    }else if(System::keyIsPressed(System::Key::KEY_s)){
        camera.dist += speed;
    }else if(System::keyIsPressed(System::Key::KEY_RIGHT)){
        camera.angle.yaw.rotateRadian(speed);
    }else if(System::keyIsPressed(System::Key::KEY_LEFT)){
        camera.angle.yaw.rotateRadian(-speed);
    }else if(System::keyIsPressed(System::Key::KEY_UP)){
        camera.angle.pitch.rotateRadian(speed);
    }else if(System::keyIsPressed(System::Key::KEY_DOWN)){
        camera.angle.pitch.rotateRadian(-speed);
    }
    
    camera.viewMatrix.setIdentity();
    camera.viewMatrix.lookAt(pos, zero, up);
}
