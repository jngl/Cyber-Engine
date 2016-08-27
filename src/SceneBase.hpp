#pragma once

#include <list>

#include "Entity.hpp"
#include "Renderer/Camera.hpp"

class SceneBase
{
public:
    SceneBase();
    
    void render();
    virtual void update() = 0;
    
protected:
    Entity& createEntity();
    
    Camera mCamera;
    
    std::list<Entity> mEntitys;
};


namespace Scene
{
    SceneBase* createScene(std::string name);
    void destroyScene(SceneBase* scene);
}
