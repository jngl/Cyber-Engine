#pragma once

#include "VoxelScene.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

#include "Math/Vector4.hpp"

class VoxelRenderer
{
public:
    VoxelRenderer(int screenWidth, int screenHeight);
    
    void loadScene();
    
    void render(uint32_t* screen);
    
    void save();
	
	VoxelScene& getSceneRef();
    
private:
    VoxelScene scene;
	int mScreenWidth;
	int mScreenHeight;
        
    float intbound(float s, float ds);
    void startPos(math::Vector3f& voxelPos, math::Vector3f& tMax, math::Vector3f rayDir);
    bool isBlock(math::Vector3f pos);
    bool raycast(math::Vector3f rayDir, math::Vector3f& normal, math::Vector3f& pos);
    math::Vector3f renderPixel(math::Vector2f pixelCoord);
};
