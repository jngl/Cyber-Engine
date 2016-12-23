#pragma once

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

float randFloatFromVec2(glm::vec2 n);

float interpolation(float a, float b, float alpha);

float noise(glm::vec2 p, glm::vec2 size);
