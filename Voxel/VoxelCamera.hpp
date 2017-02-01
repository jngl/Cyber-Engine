#pragma once

#include "Math/Vector3.hpp"
#include "Math/Vector2.hpp"

class VoxelCamera
{
public:
    VoxelCamera();
    
    void set(math::Vector3f pos, math::Vector3f view);
    
    math::Vector3f getPosition();
    math::Vector3f getView();
    
    math::Vector3f getRaydir(math::Vector2f uv);
    
private:
    math::Vector3f mPosition;
    math::Vector3f mView;
};
