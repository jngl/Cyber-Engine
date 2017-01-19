#include "VoxelCamera.hpp"

const glm::vec3 camUp=glm::vec3(0.0f, 1.0f, 0.0f);

VoxelCamera::VoxelCamera(){
    set(glm::vec3(-50, 50, -50), glm::vec3(0, 0.0f, 0.0f));
}
    
void VoxelCamera::set(glm::vec3 pos, glm::vec3 view){
    mPosition = pos;
    mView = view;
}
    
glm::vec3 VoxelCamera::getPosition(){
    return mPosition;
}

glm::vec3 VoxelCamera::getView(){
    return mView;
}

glm::vec3 VoxelCamera::getRaydir(glm::vec2 uv){
    glm::vec3 camDir=glm::normalize(mView-mPosition);
  	glm::vec3 u=glm::normalize(glm::cross(camUp,camDir));
  	glm::vec3 v=glm::cross(camDir,u);
  	glm::vec3 vcv=(mPosition+camDir);
  	glm::vec3 scrCoord=vcv+uv.x*u*0.8f+uv.y*v*0.8f;
  	glm::vec3 rayDir=scrCoord-mPosition;
    return rayDir;
}
