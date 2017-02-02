#include "VoxelCamera.hpp"

const math::Vector3f camUp{0.0f, 1.0f, 0.0f};

VoxelCamera::VoxelCamera(){
    
}
    
void VoxelCamera::set(math::Vector3f pos, math::Vector3f view){
    mPosition = pos;
    mView = view;
}
    
math::Vector3f VoxelCamera::getPosition(){
    return mPosition;
}

math::Vector3f VoxelCamera::getView(){
    return mView;
}

math::Vector3f VoxelCamera::getRaydir(math::Vector2f uv){
    math::Vector3f camDir=mView-mPosition;
	camDir.normalize();
  	math::Vector3f u;
	u =camUp.getCrossProduct(camDir);
	u.normalize();
  	math::Vector3f v;
	v = camDir.getCrossProduct(u);
  	math::Vector3f vcv=(mPosition+camDir);
  	math::Vector3f scrCoord=vcv+u*uv.x*0.8f+v*uv.y*0.8f;
  	math::Vector3f rayDir=scrCoord-mPosition;
    return rayDir;
}
