#include "Renderer.hpp"

#include "Core/PoolAllocator.hpp"

#include "../PlatformIndependenceLayer/GraphicsWrapper.hpp"

unsigned int spriteNbVertices = 4;
const float spriteVertices[] = {0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f,
                                        1.f, 1.f, 0.f,
                                        1.f, 0.f, 0.f
};
const float spriteTexCoord[] = {0.f, 0.f,
                                        0.f, 1.f,
                                        1.f, 1.f,
                                        1.f, 0.f
};
const float spriteNormals[] = {0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f
};
unsigned int spriteNbFaces = 2;
const unsigned int spriteFaces[] = { 0, 1, 2,  0, 2, 3};

namespace Renderer
{
    //main
    GraphicsWrapper::Shader defaultShader;
    GraphicsWrapper::Shader noLightShader;
    
    GraphicsWrapper::Mesh spriteMesh;
    
    void createRenderer(){
        GraphicsWrapper::createShader(defaultShader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
        GraphicsWrapper::createShader(noLightShader,
                 "../data/shaders/noLight.vert",
                 "../data/shaders/noLight.frag");
        GraphicsWrapper::createMesh(&spriteMesh,
                     spriteNbVertices,
                     spriteVertices,
                     spriteTexCoord,
                     spriteNormals,
                     spriteNbFaces,
                     spriteFaces);
    }
    
    void destroyRenderer(){
        destroyShader(defaultShader);
        destroyShader(noLightShader);
    }
    
    //material
    struct Material{
        Texture_handle texture;
    };
    core::PoolAllocator<Material, 100> MaterialPool;
    
    Material_handle createMaterial(Texture_handle tex){
        Material_handle result = MaterialPool.create();
        result->texture = tex;
        return result;
    }
    
    void destroyMaterial(Material_handle handle){
        MaterialPool.destory(handle);
    }
    

    //Model 
    struct Model{
        GraphicsWrapper::Mesh mesh;
        Material_handle material;
    };
    core::PoolAllocator<Model, 100> ModelPool;
    
    Model_handle createModel(unsigned int nbVertices,
                     const float* vertices,
                     const float* texCoord,
                     const float* normals,
                     unsigned int nbFaces,
                     const unsigned int* faces,
                     Material_handle material)
    {
        Model_handle result = ModelPool.create();
        GraphicsWrapper::createMesh(&result->mesh, nbVertices, vertices, texCoord, normals, nbFaces, faces);
        result->material = material;
        return result;
    }
    
    void destoryModel(Model_handle handle){
        GraphicsWrapper::destroyMesh(&handle->mesh);
        ModelPool.destory(handle);
    }
    
    
    //Object
    struct Object{
        Model_handle model;
        math::Matrix4f matrix;
    };
    core::PoolAllocator<Object, 100> ObjectPool;
    
    Object_handle createObject(Model_handle handle){
        Object_handle result = ObjectPool.create();
        result->model = handle;
        result->matrix.setIdentity();
        return result;
    }
    
    void destroyObject(Object_handle handle){
        ObjectPool.destory(handle);
    }
    
    math::Matrix4f& getObjectMatrixRef(Object_handle handle){
        return handle->matrix;
    }
    
    //Texture
    struct Texture{
        GraphicsWrapper::Texture mTexture;
    };
    core::PoolAllocator<Texture, 100> TexturePool;
    
    Texture_handle createTexture(const char* filename){
        Texture_handle result = TexturePool.create();
        GraphicsWrapper::createTexture(&result->mTexture, filename);
        return result;
    }
    
    void destroyTexture(Texture_handle handle){
        TexturePool.destory(handle);
    }
    
    
    //camera
    struct Camera{
        math::Matrix4f mViewMatrix;
        math::Matrix4f mProjectionMatrix;
    };
    core::PoolAllocator<Camera, 100>CameraPool;
    Camera_handle activeCamera;
    
    Camera_handle createCamera(){
        Camera_handle result = CameraPool.create();
        result->mViewMatrix.setIdentity();
        result->mProjectionMatrix.projectPerspective(M_PI/4.f, 4.0f / 3.0f, 0.1f, 100.f);
        return result;
    }
    
    void destroyCamera(Camera_handle handle){
        CameraPool.destory(handle);
    }
    
    math::Matrix4f& getCameraViewMatrixRef(Camera_handle handle){
        return handle->mViewMatrix;
    }
    
    math::Matrix4f& getCameraProjectionMatrixRef(Camera_handle handle){
        return handle->mProjectionMatrix;
    }
    
    void setActiveCamera(Camera_handle handle){
        activeCamera = handle;
    }
    
    void renderObject(Object_handle handle){
        math::Matrix4f MVP = activeCamera->mProjectionMatrix * activeCamera->mViewMatrix* handle->matrix;
        GraphicsWrapper::setTexture(&handle->model->material->texture->mTexture, &defaultShader);
        GraphicsWrapper::drawMesh(&handle->model->mesh, MVP, defaultShader);
    }
    
    
    //sprite
    struct Sprite{
        Texture_handle mTexture;
        math::Matrix4f mMatrix;
    };
    core::PoolAllocator<Sprite, 100> SpritePool;
    
    Sprite_handle createSprite(Texture_handle handle){
        Sprite_handle result = SpritePool.create();
        result->mMatrix.setIdentity();
        result->mTexture = handle;
        return result;
    }
    
    void destroySprite(Sprite_handle sprite){
        SpritePool.destory(sprite);
    }
    
    math::Matrix4f& getSpriteMatrixRef(Sprite_handle handle){
        return handle->mMatrix;
    }
    
    void renderSprite(Sprite_handle handle){
        math::Matrix4f MVP = activeCamera->mProjectionMatrix * activeCamera->mViewMatrix* handle->mMatrix;
        GraphicsWrapper::setTexture(&handle->mTexture->mTexture, &noLightShader);
        GraphicsWrapper::drawMesh(&spriteMesh, MVP, noLightShader);
    }
}
