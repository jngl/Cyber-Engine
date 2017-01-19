#pragma once

#include "Image.hpp"
#include "Noise.hpp"
#include "VoxelCamera.hpp"

class VoxelScene
{
public:
    VoxelScene();
    
    void load();
    
    bool isBlock(glm::vec3 pos);
    glm::vec3 getColor(glm::vec3 pos);
    
    void save();
    
    VoxelCamera& getCameraRef();
    
private:
    Image heightMap;
    Image texture;
    VoxelCamera camera;
    
    constexpr static float MOUNTAIN_WIDTH =  0.9f;
    constexpr static float MOUNTAIN_HEIGHT = 20.0f;
    
    float perlinnoise(glm::vec2 p);
};
