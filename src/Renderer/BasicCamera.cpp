#include "BasicCamera.hpp"

#include "../System.hpp"

void updateBasicCamera(BasicCamera& camera, float frameTime){
    const float speed = frameTime;
    
    if(System::keyIsPressed(System::Key::KEY_z)){
        camera.dist -= speed*camera.dist;
    }else if(System::keyIsPressed(System::Key::KEY_s)){
        camera.dist += speed*camera.dist;
    }else if(System::keyIsPressed(System::Key::KEY_RIGHT)){
        camera.angle.x += speed;
    }else if(System::keyIsPressed(System::Key::KEY_LEFT)){
        camera.angle.x -= speed;
    }else if(System::keyIsPressed(System::Key::KEY_UP)){
        camera.angle.y += speed;
    }else if(System::keyIsPressed(System::Key::KEY_DOWN)){
        camera.angle.y -= speed;
    }
    
    camera.viewMatrix.setIdentity();
    camera.viewMatrix.addTranslation(math::Vector3f{0.0f, 0.0f, -camera.dist});
    camera.viewMatrix.addRotation(camera.angle.y, math::Vector3f{-1.0f, 0.0f, 0.0f});
    camera.viewMatrix.addRotation(camera.angle.x, math::Vector3f{0.0f, 1.0f, 0.0f});
}
