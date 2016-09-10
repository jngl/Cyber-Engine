#pragma once

#include "../Math/Angle3.hpp"
#include "../Math/Matrix4.hpp"

struct BasicCamera
{
    float dist;
    math::Angle3f angle;
    math::Matrix4f viewMatrix;
};

void updateBasicCamera(BasicCamera& camera);
