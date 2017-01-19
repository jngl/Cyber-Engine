#include "VoxelRenderer.hpp"

#include <iostream>

VoxelRenderer::VoxelRenderer():
result(150, 100)
{
}
    
void VoxelRenderer::loadScene(){
    scene.load();
}

void VoxelRenderer::render(){
    glm::vec3 fragColor;
    glm::vec2 fragCoord;
    
    Timer timer;
    
    for(int y(result.getHeight()-1); y>=0; --y){
        for(int x(0); x<result.getWidth(); ++x){
             result.getPixelRef(x, y) = renderPixel(glm::vec2(x, y));
        }
    }
    
    std::cout<<"\rtime : "<<timer.timeInSecond()<<std::endl;
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
	pos = glm::mod(pos, 1.0f);
	// problem is now pos+t*dir = 1
	return (1.0f-pos)/dir;
}

void VoxelRenderer::startPos(glm::vec3& voxelPos, glm::vec3& tMax, glm::vec3 camPos, glm::vec3 rayDir){
	voxelPos=glm::floor(camPos);
    tMax.x = intbound(camPos.x, rayDir.x);
    tMax.y = intbound(camPos.y, rayDir.y);
    tMax.z = intbound(camPos.z, rayDir.z);
}

glm::vec4 VoxelRenderer::raycast(glm::vec3 rayDir, glm::vec3& normal){
    glm::vec3 camPos = scene.getCameraRef().getPosition();
	glm::vec3 rayStep=glm::sign(rayDir);
	glm::vec3 delta=rayStep/rayDir;
    
    glm::vec3 tMax, voxelPos;
    startPos(voxelPos, tMax, camPos, rayDir);
	
	glm::bvec3 mask;
    
    glm::vec3 fmask(mask) ;
	
	for(int i=0; i<RENDER_DIST;++i){
		glm::bvec3 b1 = glm::lessThan(tMax.xyz(), tMax.yzx());
		glm::bvec3 b2 = glm::lessThanEqual(tMax.xyz(), tMax.zxy());
		mask.x = b1.x && b2.x;
		mask.y = b1.y && b2.y;
		mask.z = b1.z && b2.z;
        
         fmask = glm::vec3(mask) ;
		
		tMax +=fmask * delta;
		voxelPos += fmask * rayStep;
		
       if(scene.isBlock(voxelPos)){
			normal = -fmask*rayStep;
			return glm::vec4(voxelPos, 1.0f);
		}
	}
	return glm::vec4(voxelPos, -1.0f);
}

glm::vec3 VoxelRenderer::renderPixel(glm::vec2 pixelCoord)
{
	glm::vec2 uv = (pixelCoord / result.getSize())*2.0f-1.0f;        //pixel coord (-1, 1)
	glm::vec3 rayDir = scene.getCameraRef().getRaydir(uv);     //ray dir
	
	//raycast
	glm::vec3 normal;
	glm::vec4 ret=raycast(rayDir, normal);
	glm::vec3 p=glm::floor(ret.xyz());
	float sky=ret.w;
	
	//color
	glm::vec3 light=glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 fragColor=glm::vec3(75.f, 75.f, 255.f);
	
	if(sky>0.0f){
        fragColor = scene.getColor(p);
		float diff=glm::max(glm::dot(light, normal), 0.0f);
		diff=diff*0.3f+0.7f;
        fragColor*=diff;
	}
	return fragColor;
}
