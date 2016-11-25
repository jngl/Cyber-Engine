#include "BasicCamera.hpp"

#include "../System.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void updateBasicCamera(BasicCamera& camera){
    const float speed = 0.0001f;
    
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
    
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -camera.dist));
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, camera.angle.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    camera.viewMatrix = glm::rotate(ViewRotateX, camera.angle.x, glm::vec3(0.0f, 1.0f, 0.0f));
}
