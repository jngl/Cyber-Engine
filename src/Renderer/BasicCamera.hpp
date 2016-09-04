#pragma once

#include "../Math/Angle3.hpp"


struct BasicCamera
{
    float dist;
    math::Angle3f angle;
};

void updateBasicCamera(BasicCamera& camera);
