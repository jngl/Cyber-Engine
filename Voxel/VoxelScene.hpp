#pragma once

#include "Image.hpp"
#include "Core/Noise.hpp"
#include "VoxelCamera.hpp"

class VoxelScene
{
public:
    VoxelScene();
    
    void load();
    
    bool isBlock(math::Vector3f pos);
    math::Vector3f getColor(math::Vector3f pos);
    
    void save();
    
    VoxelCamera& getCameraRef();
	
	constexpr static int sizeScene = 50;
	constexpr static float sizeSceneF = 50.f;
    
    constexpr static float MOUNTAIN_WIDTH =  0.9f;
    constexpr static float MOUNTAIN_HEIGHT = 25.0f;
    
private:
    Image heightMap;
    Image texture;
    VoxelCamera camera;
    
    float genHeight(math::Vector2f p);
};
