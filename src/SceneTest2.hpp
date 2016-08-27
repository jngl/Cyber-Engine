#pragma once

#include "SceneBase.hpp"


class SceneTest2 : public SceneBase
{
public:
    static constexpr auto NAME = "Test2";
    
    SceneTest2();
    ~SceneTest2();
    
    virtual void update();
private:
    Mesh* mCube;
    float time;
    Entity* mEntity;
};
