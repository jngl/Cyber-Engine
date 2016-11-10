#include "Test1.hpp"

#include "System.hpp"

#include "Voxel.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/BasicCamera.hpp"
#include "Renderer/CubeData.hpp"

#include <iostream>
#include <cassert>
using namespace std;

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

void test1(){ 
    Renderer::createRenderer();
    
    BasicCamera cam;
    cam.dist=20.f;
    
    typedef VoxelChunk<10, 10, 10> MyVoxelChunk;
    
    MyVoxelChunk voxels;
    for(std::size_t y(0); y<MyVoxelChunk::SIZE_Y; ++y){
        for(std::size_t z(0); z<MyVoxelChunk::SIZE_Z; ++z){
            for(std::size_t x(0); x<MyVoxelChunk::SIZE_X; ++x){
                if(x+5>y)
                    voxels.at(x, y, z) = VoxelType::STONE;
                else
                    voxels.at(x, y, z) = VoxelType::AIR;
            }
        }
    }
    
    VoxelChunkMesh<MyVoxelChunk> voxMesh(voxels);
    
    
    Renderer::Mesh mesh;
    createMesh(&mesh,
               voxMesh.getVerticesSize(),
               voxMesh.getPositions(),
               voxMesh.getTexCoord(),
               voxMesh.getNormal(),
               voxMesh.getIndexSize(),
               voxMesh.getFaces());
    
    
    Renderer::Shader shader;
    Renderer::createShader(shader,
                 "../data/shaders/basic.vert",
                 "../data/shaders/basic.frag");
    
    Renderer::Texture tex;
    Renderer::createTexture(&tex, "../data/byNobiax/pattern_391/diffuse.dds");
    
    glm::mat4 model(1.0f);
    
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f); 
    
    while(System::isRunning()){
        System::doEvent();
        System::clear();
     
        updateBasicCamera(cam);
        
        Renderer::setTexture(&tex, &shader);
        
       model = glm::translate(glm::mat4(1.0f), glm::vec3(-5, -5, -5));
        
        glm::mat4 MVP = proj * cam.viewMatrix * model;
        
        Renderer::drawMesh(&mesh, MVP, shader);
        
        /*for(std::size_t y(0); y<MyVoxelChunk::SIZE_Y; ++y){
            for(std::size_t z(0); z<MyVoxelChunk::SIZE_Z; ++z){
                for(std::size_t x(0); x<MyVoxelChunk::SIZE_X; ++x){
                    if(voxels.at(x, y, z)!=VoxelType::AIR){
                        model = glm::translate(glm::mat4(1.0f), glm::vec3(x-MyVoxelChunk::SIZE_X/2.f, y-MyVoxelChunk::SIZE_Y/2.f, z-MyVoxelChunk::SIZE_Z/2.f));
                        
                        glm::mat4 MVP = proj * cam.viewMatrix * model;
                        
                        Renderer::drawMesh(&mesh, MVP, shader);
                    }
                }
            }
        }*/
        System::endFrame();
    }
    
    Renderer::destroyTexture(&tex);
    Renderer::destroyRenderer();
}
