#pragma once

#include "Image.hpp"
#include "Noise.hpp"

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
    Image heightMap;
    Image texture;
    
    constexpr static float MOUNTAIN_WIDTH =  0.9f;
    constexpr static float MOUNTAIN_HEIGHT = 20.0f;
    
     constexpr static int  RENDER_DIST  =150;
     constexpr static float  SPEED = 20.0f;
     constexpr static float  CAM_DIST = 70.0f;
        
    float perlinnoise(glm::vec2 p);
    float intbound(float s, float ds);
    glm::vec3 intbound(glm::vec3 s, glm::vec3 ds);
    bool isBlock(glm::vec3 pos);
    glm::vec4 raycast(glm::vec3 camPos, glm::vec3 rayDir, glm::vec3& normal);
    void mainImage( glm::vec3& fragColor, glm::vec2 fragCoord, glm::vec2 iResolution, float iGlobalTime, glm::vec3& camPos, glm::vec3& camView);
};
