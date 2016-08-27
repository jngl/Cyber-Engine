#include "SceneTest2.hpp"


SceneTest2::SceneTest2():
        time(0.f)
{
    //inti mesh
    MeshData data;
    data.makeCube();
    mCube = new Mesh(data);
    
    mEntity = &createEntity();
    mEntity->position.set(0.f, 0.f, -5.0f);
    mEntity->mesh = mCube;
}

SceneTest2::~SceneTest2(){
    delete mCube;
}

void SceneTest2::update(){
    time += 0.015f;
    mEntity->rotation.yaw.setDegree(time);
}
