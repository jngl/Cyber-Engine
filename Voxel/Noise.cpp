#include "Noise.hpp"

float randFloatFromVec2(glm::vec2 n){
    return glm::fract(sin(glm::dot(n, glm::vec2(12.9898f, 78.233f)))* 43758.5453f);
}

float interpolation(float a, float b, float alpha){
	return glm::mix(a, b, 0.5f-cos(alpha*3.14f)/2.0f);
}

float noise(glm::vec2 p, glm::vec2 size){
	
	
	float h11=randFloatFromVec2(glm::vec2(floor(p.x/size.x), floor(p.y/size.y)));
	float h12=randFloatFromVec2(glm::vec2(floor(p.x/size.x), floor(p.y/size.y+1.0)));
	float h21=randFloatFromVec2(glm::vec2(floor(p.x/size.x+1.0), floor(p.y/size.y)));
	float h22=randFloatFromVec2(glm::vec2(floor(p.x/size.x+1.0), floor(p.y/size.y+1.0)));
	
	float px=glm::fract(p.x/size.x);
	float py=glm::fract(p.y/size.y);
	
	return interpolation(interpolation(h11, h21, px), interpolation(h12, h22, px), py);
}
