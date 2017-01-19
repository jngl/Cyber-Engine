#pragma once

#include "VoxelScene.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

class VoxelRenderer
{
public:
    VoxelRenderer();
    
    void loadScene();
    
    void render();
    
    void save();
    
private:
    Image result;
    VoxelScene scene;
    
     constexpr static int  RENDER_DIST  =150;
     constexpr static float  SPEED = 20.0f;
     constexpr static float  CAM_DIST = 70.0f;
        
    float intbound(float s, float ds);
    void startPos(glm::vec3& voxelPos, glm::vec3& tMax, glm::vec3 camPos, glm::vec3 rayDir);
    bool isBlock(glm::vec3 pos);
    glm::vec4 raycast(glm::vec3 rayDir, glm::vec3& normal);
    glm::vec3 renderPixel(glm::vec2 pixelCoord);
};
