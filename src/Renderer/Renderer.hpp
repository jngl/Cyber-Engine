#pragma once

#include "Math/Matrix4.hpp"

namespace Renderer
{
    struct Material;
    struct Model;
    struct Object;
    struct Texture;
    struct Camera;
    struct Sprite;

    typedef Material* Material_handle;
    typedef Texture* Texture_handle;
    typedef Model* Model_handle;
    typedef Object* Object_handle;
    typedef Camera* Camera_handle;
    typedef Sprite* Sprite_handle;
    
    //main
    void createRenderer();
    void destroyRenderer();
    
    //material
    Material_handle createMaterial(Texture_handle tex);
    void destroyMaterial(Material_handle handle);

    //Model 
    Model_handle createModel(unsigned int nbVertices,
                     const float* vertices,
                     const float* texCoord,
                     const float* normals,
                     unsigned int nbFaces,
                     const unsigned int* faces,
                     Material_handle material
                            );
    void destoryModel(Model_handle handle);
    
    //Object
    Object_handle createObject(Model_handle handle);
    void destroyObject(Object_handle handle);
    math::Matrix4f& getObjectMatrixRef(Object_handle handle);
    void renderObject(Object_handle handle);
    
    //Texture
    Texture_handle createTexture(const char* filename);
    void destroyTexture(Texture_handle handle);
    
    //camera
    Camera_handle createCamera();
    void destroyCamera(Camera_handle handle);
    math::Matrix4f& getCameraViewMatrixRef(Camera_handle handle);
    math::Matrix4f& getCameraProjectionMatrixRef(Camera_handle handle);
    void setActiveCamera(Camera_handle handle);
    
    //sprite
    Sprite_handle createSprite(Texture_handle handle);
    void destroySprite(Sprite_handle sprite);
    math::Matrix4f& getSpriteMatrixRef(Sprite_handle handle);
    void renderSprite(Sprite_handle handle);
}

