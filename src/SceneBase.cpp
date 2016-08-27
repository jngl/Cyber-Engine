#include "SceneBase.hpp"
#include "SceneTest2.hpp"
#include "Core/Error.hpp"

#include <GL/glew.h>

SceneBase::SceneBase(){
    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void SceneBase::render(){
    mCamera.use();
    for(Entity &e : mEntitys){
        e.draw();
    }
}

Entity& SceneBase::createEntity(){
    mEntitys.emplace_front();
    return mEntitys.front();
}

namespace Scene
{
    SceneBase* createScene(std::string name){
        SceneBase* scene;
        if(name==SceneTest2::NAME){
            scene = new SceneTest2();
        }else{
            throw core::Error("Scene \""+name+"\" don't exist");
        }
        return scene;
    }
    void destroyScene(SceneBase* scene){
        if(scene){
            delete scene;
        }
    }
}
