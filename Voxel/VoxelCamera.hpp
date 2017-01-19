#pragma once

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

class VoxelCamera
{
public:
    VoxelCamera();
    
    void set(glm::vec3 pos, glm::vec3 view);
    
    glm::vec3 getPosition();
    glm::vec3 getView();
    
    glm::vec3 getRaydir(glm::vec2 uv);
    
private:
    glm::vec3 mPosition;
    glm::vec3 mView;
};
