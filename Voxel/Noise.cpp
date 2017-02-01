#include "Noise.hpp"

#include "Math/MathUtils.hpp"

#include <cassert>

float randFloatFromVec2(math::Vector2f n){
	return 0.5f + 0.5f * math::fract(
			math::sin(
				n.getDotProduct(
					{12.9898f, 78.233f}
				)
			)
			*
			43758.5453f
		);
}
/*
float randFloatFromVec2(math::Vector2f n){
    return math::fract(sin(n.getDotProduct({12.9898f, 78.233f}))* 43758.5453f);
}*/

float interpolation(float a, float b, float alpha){
	return math::mix(a, b, 0.5f-math::cos(alpha*3.14f)/2.0f);
}

float noise(math::Vector2f p, math::Vector2f size){
	float h11=randFloatFromVec2(math::Vector2f{math::floor(p.x/size.x), math::floor(p.y/size.y)});
	float h12=randFloatFromVec2(math::Vector2f{math::floor(p.x/size.x), math::floor(p.y/size.y+1.0f)});
	float h21=randFloatFromVec2(math::Vector2f{math::floor(p.x/size.x+1.0f), math::floor(p.y/size.y)});
	float h22=randFloatFromVec2(math::Vector2f{math::floor(p.x/size.x+1.0f), math::floor(p.y/size.y+1.0f)});
	
	float px=math::fract(p.x/size.x);
	float py=math::fract(p.y/size.y);
	
	assert(h11>=0.f && h11<1.f);
	assert(h12>=0.f && h12<1.f);
	assert(h21>=0.f && h21<1.f);
	assert(h22>=0.f && h22<1.f);
	
	return interpolation(interpolation(h11, h21, px), interpolation(h12, h22, px), py);
}

