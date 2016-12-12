#include <iostream>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#define RENDER_DIST 400
#define SPEED 20.0f
#define CAM_DIST 70.0f

//montaigne scale
#define HEIGHT 200.0f
#define WIDTH 0.3f

float randFloatFromVec2(glm::vec2 n)
{
  return 0.5f + 0.5f * glm::fract(sin(glm::dot(n, glm::vec2(12.9898f, 78.233f)))* 43758.5453f);
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

float perlinnoise(glm::vec2 p){
	return ( noise(p*WIDTH, glm::vec2(8.0f)) * 0.25f+noise(p*WIDTH, glm::vec2(32.0f)) )*HEIGHT;	
}

float mymod(float value, float modulus) {
  return glm::mod((glm::mod(value, modulus) + modulus), modulus);
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

void mainImage( glm::vec4& fragColor, glm::vec2 fragCoord, glm::vec2 iResolution, float iGlobalTime)
{
	//pixel coord (-1, 1)
	glm::vec2 uv = (fragCoord / iResolution)*2.0f-1.0f;
	
	//camera
	glm::vec3 camPos=glm::vec3(CAM_DIST-iGlobalTime*SPEED, HEIGHT*1.4f, 150.0f);
	camPos.y=perlinnoise(camPos.xz())+CAM_DIST*0.25f;
	
	glm::vec3 camView=glm::vec3(-iGlobalTime*SPEED, 0.0f, 50.0f);
	camView.y=perlinnoise(camView.xz());

	glm::vec3 camUp=glm::vec3(0.0f, 1.0f, 0.0f);
	
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
	glm::vec3 color=glm::vec3(0.3f, 0.3f, 1.0f);
	float diff=1.0f;
	
	if(sky>0.0f){
		color=glm::vec3(p.y/HEIGHT, p.x/150.0f+0.5f, p.z/150.0f+0.5f);
		//color=texture2D(iChannel0, p.xz/150.0).xyz;
		diff=glm::max(glm::dot(light, normal), 0.0f);
		diff=diff*0.3f+0.7f;
	}
	
	//fin
	fragColor = glm::vec4(color*diff,1.0f);
}

int main(){
    glm::vec4 fragColor;
    glm::vec2 fragCoord;
    glm::vec2 iResolution(60.f, 40.f);
    float iGlobalTime(0.f);
    
    std::cout<<"P3"<<std::endl;
    std::cout<<glm::floor(iResolution.x)<<" "<<glm::floor(iResolution.y)<<std::endl;
    std::cout<<"255"<<std::endl;
    
    for(int y(iResolution.y-1); y>=0; --y){
        for(int x(0); x<iResolution.x; ++x){
            fragCoord = glm::vec2(x, y);
            mainImage(fragColor, fragCoord, iResolution, iGlobalTime);
            fragColor = glm::max(glm::vec4(0.f), fragColor*255.f);
            std::cout<<glm::floor(fragColor.x)<<" "<<glm::floor(fragColor.y)<<" "<<glm::floor(fragColor.z)<<" ";
            
        }
        std::cout<<std::endl;
        std::cerr<<"\r"<<y<<std::endl;
    }
    
    return 0;
}


