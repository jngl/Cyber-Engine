#pragma once

#include "Math/Matrix4.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector2.hpp"

struct BasicCamera
{
    float dist;
    math::Vector2f angle;
    math::Matrix4f viewMatrix;
};

void updateBasicCamera(BasicCamera& camera, float frameTime);
