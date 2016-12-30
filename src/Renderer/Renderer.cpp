#include "Renderer.hpp"

#include "Core/PoolAllocator.hpp"

#include "../PlatformIndependenceLayer/GraphicsWrapper.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Renderer
{
    //main
    GraphicsWrapper::Shader defaultShader;
    
    void createRenderer(){
        GraphicsWrapper::createShader(defaultShader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    }
    
    void destroyRenderer(){
        destroyShader(defaultShader);
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
        glm::mat4 matrix;
    };
    core::PoolAllocator<Object, 100> ObjectPool;
    
    Object_handle createObject(Model_handle handle){
        Object_handle result = ObjectPool.create();
        result->model = handle;
        result->matrix = glm::mat4(1.0);
        return result;
    }
    
    void destroyObject(Object_handle handle){
        ObjectPool.destory(handle);
    }
    
    glm::mat4& getObjectMatrixRef(Object_handle handle){
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
        glm::mat4 mViewMatrix;
        glm::mat4 mProjectionMatrix;
    };
    core::PoolAllocator<Camera, 100>CameraPool;
    Camera_handle activeCamera;
    
    Camera_handle createCamera(){
        Camera_handle result = CameraPool.create();
        result->mViewMatrix = glm::mat4(1.0f);
        result->mProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
        return result;
    }
    
    void destroyCamera(Camera_handle handle){
        CameraPool.destory(handle);
    }
    
    glm::mat4& getCameraViewMatrixRef(Camera_handle handle){
        return handle->mViewMatrix;
    }
    
    glm::mat4& getCameraProjectionMatrixRef(Camera_handle handle){
        return handle->mProjectionMatrix;
    }
    
    void setActiveCamera(Camera_handle handle){
        activeCamera = handle;
    }
    
    
    
    
    
    void renderObject(Object_handle handle){
        glm::mat4 MVP = activeCamera->mProjectionMatrix * activeCamera->mViewMatrix* handle->matrix;
        GraphicsWrapper::setTexture(&handle->model->material->texture->mTexture, &defaultShader);
        GraphicsWrapper::drawMesh(&handle->model->mesh, MVP, defaultShader);
    }
    
}
