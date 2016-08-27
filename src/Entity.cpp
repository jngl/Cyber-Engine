#include "Entity.hpp"


Entity::Entity():
    mesh(nullptr)
{
}

void Entity::draw(){
    if(mesh){
        glLoadIdentity( );
        
        glTranslatef(position.x,
                     position.y,
                     position.z);
        
        glRotatef(rotation.yaw.getDegree(), 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.pitch.getDegree(), 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.roll.getDegree(), 0.0f, 0.0f, 1.0f);
        mesh->draw();
    }
}
