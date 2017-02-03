#include "VoxelCamera.hpp"

const math::Vector3f camUp{0.0f, 1.0f, 0.0f};

VoxelCamera::VoxelCamera(){
    
}
    
void VoxelCamera::set(math::Vector3f pos, math::Vector3f view){
    mPosition = pos;
    mView = view;
	
	mDir = mView-mPosition;
	mDir.normalize();
	
	mU = camUp.getCrossProduct(mDir);
	mU.normalize();
	
	mV = mDir.getCrossProduct(mU);
	
	mVCV = mPosition+mDir;
}
    
math::Vector3f VoxelCamera::getPosition(){
    return mPosition;
}

math::Vector3f VoxelCamera::getView(){
    return mView;
}

math::Vector3f VoxelCamera::getRaydir(math::Vector2f uv){
  	math::Vector3f scrCoord=mVCV+mU*uv.x*0.8f+mV*uv.y*0.8f;
  	math::Vector3f rayDir=scrCoord-mPosition;
    return rayDir;
}
