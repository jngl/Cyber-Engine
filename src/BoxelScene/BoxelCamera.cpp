#include "BoxelCamera.hpp"

#include "../Window.hpp"

BoxelCamera::BoxelCamera(){
  mRendererCamera = Renderer::createCamera();
  dist=30.f;
}
  
void BoxelCamera::update(float frameTime){
    const float speed = frameTime;
    
    if(System::keyIsPressed(System::Key::KEY_z)){
        dist -= speed*dist;
    }else if(System::keyIsPressed(System::Key::KEY_s)){
        dist += speed*dist;
    }else if(System::keyIsPressed(System::Key::KEY_RIGHT)){
        angle.x += speed;
    }else if(System::keyIsPressed(System::Key::KEY_LEFT)){
        angle.x -= speed;
    }else if(System::keyIsPressed(System::Key::KEY_UP)){
        angle.y += speed;
    }else if(System::keyIsPressed(System::Key::KEY_DOWN)){
        angle.y -= speed;
    }
    
    math::Matrix4f viewMatrix;
    
    viewMatrix.setIdentity();
    viewMatrix.addTranslation(math::Vector3f{0.0f, 0.0f, -dist});
    viewMatrix.addRotation(angle.y, math::Vector3f{-1.0f, 0.0f, 0.0f});
    viewMatrix.addRotation(angle.x, math::Vector3f{0.0f, 1.0f, 0.0f});
    
    Renderer::getCameraViewMatrixRef(mRendererCamera) = viewMatrix;
}
  
void BoxelCamera::setActive(){
  Renderer::setActiveCamera(mRendererCamera);
}
