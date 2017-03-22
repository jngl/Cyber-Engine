#pragma once

#include "Math/Vector2.hpp"

namespace core
{
	float randFloatFromVec2(math::Vector2f n);

	float interpolation(float a, float b, float alpha);

	float noise(math::Vector2f p, math::Vector2f size);
}
