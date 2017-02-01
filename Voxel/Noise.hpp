#pragma once

#include "Math/Vector2.hpp"

float randFloatFromVec2(math::Vector2f n);

float interpolation(float a, float b, float alpha);

float noise(math::Vector2f p, math::Vector2f size);

