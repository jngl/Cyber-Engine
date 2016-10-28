#pragma once

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

struct BasicCamera
{
    float dist;
    glm::vec2 angle;
    glm::mat4 viewMatrix;
};

void updateBasicCamera(BasicCamera& camera);
