#include "VoxelScene.hpp"

#include <cmath>
#include <cassert>
#include <iostream>

VoxelScene::VoxelScene():
heightMap(sizeScene, sizeScene),
texture(sizeScene, sizeScene)
{
}
    
void VoxelScene::load(){
    for(int y(0); y<heightMap.getHeight(); ++y){
        for(int x(0); x<heightMap.getWidth(); ++x){
            float h = genHeight(math::Vector2f{static_cast<float>(x), static_cast<float>(y)});
            heightMap.getPixelRef(x, y).setAllAxes(h);
			
			assert(h>=0.f && h<=MOUNTAIN_HEIGHT);
			
           if(h<MOUNTAIN_HEIGHT/2.f){
                texture.getPixelRef(x, y)=math::Vector3f::mix(math::Vector3f{0.f, 0.f, 0.f}, math::Vector3f{0.f, 0.f, 255.f}, h/(MOUNTAIN_HEIGHT/2.f));
            }else{
                texture.getPixelRef(x, y)=math::Vector3f::mix(math::Vector3f{0.f, 255.f, 0.f}, math::Vector3f{255.f, 255.f, 255.f}, (h-MOUNTAIN_HEIGHT/2.f)/(MOUNTAIN_HEIGHT/2.f));
            }
        }
    }
}

bool VoxelScene::isBlock(math::Vector3f pos){
	/*if(pos.x<0.f || pos.z<0.f || pos.x>=sizeSceneF || pos.z>=sizeSceneF){
		return false;
	}
	else{*/
		float h = heightMap.getPixelRef(pos.x+0.5f,pos.z+0.5f).x;
		return pos.y<h; 
	//}
}

math::Vector3f VoxelScene::getColor(math::Vector3f pos){
    return texture.getPixelRef(fmod(math::abs(pos.x), (float)texture.getWidth()), fmod(math::abs(pos.z), (float)texture.getHeight()));
}

void VoxelScene::save(){
    heightMap.save("hm.ppm");
    texture.save("tex.ppm");
}

VoxelCamera& VoxelScene::getCameraRef(){
    return camera;
}

float VoxelScene::genHeight(math::Vector2f p){
	return ( core::noise(p*MOUNTAIN_WIDTH, math::Vector2f{8.0f, 8.f}) * 0.25f + 0.75f*core::noise(p*MOUNTAIN_WIDTH, math::Vector2f{32.0f, 32.f}) )*MOUNTAIN_HEIGHT;	
}
