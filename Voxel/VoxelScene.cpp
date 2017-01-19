#include "VoxelScene.hpp"

VoxelScene::VoxelScene():
heightMap(50, 50),
texture(50, 50)
{
}
    
void VoxelScene::load(){
    for(int y(0); y<heightMap.getHeight(); ++y){
        for(int x(0); x<heightMap.getWidth(); ++x){
            float h = perlinnoise(glm::vec2(x, y));
            heightMap.getPixelRef(x, y)=glm::vec3(h);
           if(h<MOUNTAIN_HEIGHT/2.f){
                texture.getPixelRef(x, y)=glm::mix(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 255.f), h/(MOUNTAIN_HEIGHT/2.f));
            }else{
                texture.getPixelRef(x, y)=glm::mix(glm::vec3(0.f, 255.f, 0.f), glm::vec3(255.f), (h-MOUNTAIN_HEIGHT/2.f)/(MOUNTAIN_HEIGHT/2.f));
            }
        }
    }
}

bool VoxelScene::isBlock(glm::vec3 pos){
    float h = heightMap.getPixelRef(glm::mod(pos.x, (float)heightMap.getWidth()), glm::mod(pos.z, (float)heightMap.getHeight())).x;
    return pos.y<h;
}

glm::vec3 VoxelScene::getColor(glm::vec3 pos){
    return texture.getPixelRef(glm::mod(pos.x, (float)texture.getWidth()), glm::mod(pos.z, (float)texture.getHeight()));
}

void VoxelScene::save(){
    heightMap.save("hm.ppm");
    texture.save("tex.ppm");
}

VoxelCamera& VoxelScene::getCameraRef(){
    return camera;
}

float VoxelScene::perlinnoise(glm::vec2 p){
	return ( noise(p*MOUNTAIN_WIDTH, glm::vec2(8.0f)) * 0.25f+0.75f*noise(p*MOUNTAIN_WIDTH, glm::vec2(32.0f)) )*MOUNTAIN_HEIGHT;	
}
