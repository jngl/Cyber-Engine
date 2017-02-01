#include "VoxelRenderer.hpp"

#include <iostream>
#include <cassert>

#include "Math/MathUtils.hpp"

VoxelRenderer::VoxelRenderer():
result(300, 200)
{
}
    
void VoxelRenderer::loadScene(){
    scene.load();
}

void VoxelRenderer::render(){
    Timer timer;
	
	const int nbPart = 8;
	
	int part = result.getHeight() / nbPart;
    
	#pragma omp parallel for
	for(int y=0; y<result.getHeight(); ++y){
        for(int x(0); x<result.getWidth(); ++x){
             result.getPixelRef(x, y) = renderPixel(math::Vector2f{static_cast<float>(x), static_cast<float>(y)});
        }
    }
    
    std::cout<<"time : "<<timer.timeInSecond()<<std::endl;
	std::cout<<"FPS : "<<1.f/timer.timeInSecond()<<std::endl;
}

void VoxelRenderer::save(){
    scene.save();
    result.save("result.ppm");
}

float VoxelRenderer::intbound(float pos, float dir) {
	// Find the smallest positive t such that pos+t*dir is an integer.
	if (dir < 0.0f) {
		pos=-pos;
		dir=-dir;
	}
	pos = math::fract(pos);
	// problem is now pos+t*dir = 1
	return (1.0f-pos)/dir;
}

void VoxelRenderer::startPos(math::Vector3f& voxelPos, math::Vector3f& tMax, math::Vector3f rayDir){
	math::Vector3f camPos = scene.getCameraRef().getPosition();
	voxelPos=camPos.getFloor();
    tMax.x = intbound(camPos.x, rayDir.x);
    tMax.y = intbound(camPos.y, rayDir.y);
    tMax.z = intbound(camPos.z, rayDir.z);
}

bool VoxelRenderer::raycast(math::Vector3f rayDir, math::Vector3f& normal, math::Vector3f& pos){
	math::Vector3f rayStep=rayDir.getSign();
	math::Vector3f delta=rayStep/rayDir;
    
    math::Vector3f tMax, voxelPos;
    startPos(voxelPos, tMax, rayDir);
	
	for(;;){
		if(tMax.x < tMax.y) {
			if(tMax.x < tMax.z) {
				voxelPos.x+=rayStep.x;
				tMax.x+= delta.x;
				normal = {-rayStep.x, 0.f, 0.f};
			} else  {
				voxelPos.z+=rayStep.z;
				tMax.z+= delta.z;
				normal = {0.f, 0.f, -rayStep.z};
			}
		} else  {
			if(tMax.y < tMax.z) {
				voxelPos.y+= rayStep.y;
				tMax.y+= delta.y;
				normal = {0.f, -rayStep.y, 0.f};
				if(rayStep.y>0 && voxelPos.y>VoxelScene::MOUNTAIN_HEIGHT){
					return false;
				}
			} else  {
				voxelPos.z+= rayStep.z;
				tMax.z+= delta.z;
				normal = {0.f, 0.f, -rayStep.z};
			}
		}
		
		if(voxelPos.z>=VoxelScene::sizeSceneF || voxelPos.x>=VoxelScene::sizeSceneF || voxelPos.x<0.f || voxelPos.z<0.f){
			return false;
		}else if(scene.isBlock(voxelPos)){
			pos = voxelPos;
			return true;
		}
	}
	return false;
}

math::Vector3f VoxelRenderer::renderPixel(math::Vector2f pixelCoord)
{
	math::Vector2f uv = (pixelCoord / result.getSize())*2.0f-1.0f;        //pixel coord (-1, 1)
	math::Vector3f rayDir = scene.getCameraRef().getRaydir(uv);     //ray dir

	math::Vector3f normal, pos;
	
	//color
	math::Vector3f light=math::Vector3f{0.0f, 1.0f, 0.0f};
	
	if(raycast(rayDir, normal, pos)){
        math::Vector3f fragColor = scene.getColor(pos);
		float diff=math::max(light.getDotProduct(normal), 0.0f);
		diff=diff*0.3f+0.7f;
        fragColor*=diff;
		return fragColor;
	}else{
		return {100.f, 100.f, 255.f};
	}
}

