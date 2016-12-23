#include <iostream>
#include <vector>
#include <fstream>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>


#include "PlatformIndependenceLayer/Timer.hpp"

#include "Image.hpp"
#include "Noise.cpp"

#define RENDER_DIST 50
#define SPEED 20.0f
#define CAM_DIST 70.0f

//montaigne scale
#define HEIGHT 20.0f
#define WIDTH 0.9f

Image result(150, 100);
Image heightMap(500, 500);
Image texture(500, 500);

const glm::vec3 camUp=glm::vec3(0.0f, 1.0f, 0.0f);

float perlinnoise(glm::vec2 p){
	return ( noise(p*WIDTH, glm::vec2(8.0f)) * 0.25f+0.75f*noise(p*WIDTH, glm::vec2(32.0f)) )*HEIGHT;	
}

float intbound(float s, float ds) {
	// Find the smallest positive t such that s+t*ds is an integer.
	if (ds < 0.0f) {
		s=-s;
		ds=-ds;
	}
	s = glm::mod(s, 1.0f);
	// problem is now s+t*ds = 1
	return (1.0f-s)/ds;
}

glm::vec3 intbound(glm::vec3 s, glm::vec3 ds){
	return glm::vec3(intbound(s.x, ds.x), intbound(s.y, ds.y), intbound(s.z, ds.z));	
}

bool isBlock(glm::vec3 pos){
    float h = heightMap.getPixelRef(glm::mod(pos.x, 500.f), glm::mod(pos.z, 500.f)).x;
    return pos.y<h;
}


glm::vec4 raycast(glm::vec3 camPos, glm::vec3 rayDir, glm::vec3& normal){
	glm::vec3 voxelPos=glm::floor(camPos);
	glm::vec3 rayStep=glm::sign(rayDir);
	glm::vec3 tMax=intbound(camPos, rayDir);
	glm::vec3 delta=rayStep/rayDir;
	
	glm::bvec3 mask;
	
	for(int i=0; i<RENDER_DIST;++i){
		glm::bvec3 b1 = glm::lessThan(tMax.xyz(), tMax.yzx());
		glm::bvec3 b2 = glm::lessThanEqual(tMax.xyz(), tMax.zxy());
		mask.x = b1.x && b2.x;
		mask.y = b1.y && b2.y;
		mask.z = b1.z && b2.z;
		
		tMax += glm::vec3(mask) * delta;
		voxelPos += glm::vec3(mask) * rayStep;
		
		if(voxelPos.y<perlinnoise(voxelPos.xz())){
			normal = -glm::vec3(mask)*rayStep;
			return glm::vec4(voxelPos, 1.0);
		}
	}
	normal = glm::vec3(mask)*rayStep;
	return glm::vec4(voxelPos, -1.0);
}

void mainImage( glm::vec3& fragColor, glm::vec2 fragCoord, glm::vec2 iResolution, float iGlobalTime, glm::vec3& camPos, glm::vec3& camView)
{
	//pixel coord (-1, 1)
	glm::vec2 uv = (fragCoord / iResolution)*2.0f-1.0f;
	
	//ray dir
	glm::vec3 camDir=glm::normalize(camView-camPos);
  	glm::vec3 u=glm::normalize(glm::cross(camUp,camDir));
  	glm::vec3 v=glm::cross(camDir,u);
  	glm::vec3 vcv=(camPos+camDir);
  	glm::vec3 scrCoord=vcv+uv.x*u*0.8f+uv.y*v*0.8f;
  	glm::vec3 rayDir=(scrCoord-camPos)*float(RENDER_DIST);
	
	//raycast
	glm::vec3 normal;
	glm::vec4 ret=raycast(camPos, rayDir, normal);
	glm::vec3 p=glm::floor(ret.xyz());
	float sky=ret.w;
	
	//color
	glm::vec3 light=glm::vec3(0.0f, 1.0f, 0.0f);
	fragColor=glm::vec3(0.3f, 0.3f, 1.0f);
	
	if(sky>0.0f){
		fragColor=glm::vec3(p.y/HEIGHT, p.x/150.0f+0.5f, p.z/150.0f+0.5f);
        //fragColor = texture.getPixelRef(glm::mod(p.x, 500.f), glm::mod(p.z, 500.f));
		float diff=glm::max(glm::dot(light, normal), 0.0f);
		diff=diff*0.3f+0.7f;
        fragColor*=diff;
	}
	fragColor*=255;
}

int main(){
    
    //gen HeightMap
    for(int y(0); y<heightMap.getHeight(); ++y){
        for(int x(0); x<heightMap.getWidth(); ++x){
            float h = perlinnoise(glm::vec2(x, y));
            heightMap.getPixelRef(x, y)=glm::vec3(h);
           if(h<HEIGHT/2.f){
                texture.getPixelRef(x, y)=glm::mix(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 255.f), h/(HEIGHT/2.f));
            }else{
                texture.getPixelRef(x, y)=glm::mix(glm::vec3(0.f, 255.f, 0.f), glm::vec3(255.f), (h-HEIGHT/2.f)/(HEIGHT/2.f));
            }
        }
    }
    
    glm::vec3 fragColor;
    glm::vec2 fragCoord;
    glm::vec2 iResolution(result.getWidth(), result.getHeight());
    float iGlobalTime(0.f);
    
    //camera
	glm::vec3 camPos=glm::vec3(-HEIGHT, 10, -HEIGHT);
    
    glm::vec3 camView=glm::vec3(0.f, 0.0f, 0.0f);
    
    Timer timer;
    
    for(int y(result.getHeight()-1); y>=0; --y){
        for(int x(0); x<result.getWidth(); ++x){
             fragCoord = glm::vec2(x, y);
            mainImage(result.getPixelRef(x, y), fragCoord, iResolution, iGlobalTime, camPos, camView);
        }
    }
    
    std::cout<<"\rtime : "<<timer.timeInSecond()<<std::endl;
    
    heightMap.save("hm.ppm");
    texture.save("tex.ppm");
    result.save("result.ppm");
}


