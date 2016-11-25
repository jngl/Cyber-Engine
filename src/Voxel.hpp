#pragma once

#include <array>
#include <vector>
#include <cstddef>
#include <iostream>

#include "Core/Error.hpp"

#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"

enum class VoxelType
{
    AIR,
    STONE,
    DIRT,
    GRASS
};

template<std::size_t sizeX, std::size_t sizeY, std::size_t sizeZ>
class VoxelChunkGrid
{
public:
    static const std::size_t SIZE_X = sizeX;
    static const std::size_t SIZE_Y = sizeY;
    static  const std::size_t SIZE_Z = sizeZ;
    
    VoxelType& at(std::size_t x, std::size_t y, std::size_t z){
        coreCheckParam(x<sizeX && y<sizeY && z<sizeZ);
        
        return voxels[y*sizeX*sizeZ + z*sizeX + x];
    }
    
private:
    std::array<VoxelType, sizeX*sizeY*sizeZ> voxels;
};


template<class MyVoxelChunk>
class VoxelChunkMesh
{
public:
    VoxelChunkMesh(MyVoxelChunk& voxels, VoxelType type)
    {
        for(std::size_t y(0); y<MyVoxelChunk::SIZE_Y; ++y){
            for(std::size_t z(0); z<MyVoxelChunk::SIZE_Z; ++z){
                for(std::size_t x(0); x<MyVoxelChunk::SIZE_X; ++x){
                    if(voxels.at(x, y, z)==type){
                        gennerateCube(voxels, x, y, z);
                    }
                }
            }
        }
    }
    
    std::size_t getVerticesSize(){
        return vertices.size()/3;
    }
    
    float* getPositions(){
        return &vertices[0];
    }
    
    float* getTexCoord(){
        return &texCoord[0];
    }
    
    float* getNormal(){
        return &normals[0];
    }
    
    std::size_t getIndexSize(){
        return faces.size();
    }
    
    uint* getFaces(){
        return &faces[0];
    }
    
private:
    void gennerateCube(MyVoxelChunk& voxels, std::size_t x, std::size_t y, std::size_t z){
        float fx = x;
        float fy = y;
        float fz = z;
        
        std::size_t vSize;
        
        //up
        if( y+1==MyVoxelChunk::SIZE_Y || voxels.at(x,y+1,z)==VoxelType::AIR ){
            addVertex(fx,     fy+1.f, fz,       0, 0,       0.f, 1.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 0,       0.f, 1.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,   1, 1,       0.f, 1.f, 0.f);
            addVertex(fx,     fy+1.f, fz+1.f,   0, 1,       0.f, 1.f, 0.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
       
        //down
        if( y==0 || voxels.at(x,y-1,z)==VoxelType::AIR ){
            addVertex(fx,     fy, fz,       0, 0,       0.f, -1.f, 0.f);
            addVertex(fx+1.f, fy, fz,       1, 0,       0.f, -1.f, 0.f);
            addVertex(fx+1.f, fy, fz+1.f,   1, 1,       0.f, -1.f, 0.f);
            addVertex(fx,     fy, fz+1.f,   0, 1,       0.f, -1.f, 0.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //left
        if( x+1==MyVoxelChunk::SIZE_X || voxels.at(x+1,y,z)==VoxelType::AIR ){
            addVertex(fx+1.f, fy,     fz,       0, 0,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 0,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,   1, 1,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy,     fz+1.f,   0, 1,       1.f, 0.f, 0.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //right
        if( x==0 || voxels.at(x-1,y,z)==VoxelType::AIR ){
            addVertex(fx, fy,     fz,       0, 0,       -1.f, 0.f, 0.f);
            addVertex(fx, fy+1.f, fz,       1, 0,       -1.f, 0.f, 0.f);
            addVertex(fx, fy+1.f, fz+1.f,   1, 1,       -1.f, 0.f, 0.f);
            addVertex(fx, fy,     fz+1.f,   0, 1,       -1.f, 0.f, 0.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //front
        if( z+1==MyVoxelChunk::SIZE_Z || voxels.at(x,y,z+1)==VoxelType::AIR ){
            addVertex(fx,     fy,     fz+1.f,       0, 0,       0.f, 0.f, 1.f);
            addVertex(fx+1.f, fy,     fz+1.f,       1, 0,       0.f, 0.f, 1.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,       1, 1,       0.f, 0.f, 1.f);
            addVertex(fx,     fy+1.f, fz+1.f,       0, 1,       0.f, 0.f, 1.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //back
        if( z==0 || voxels.at(x,y,z-1)==VoxelType::AIR ){
            
            addVertex(fx,     fy,     fz,       0, 0,       0.f, 0.f, -1.f);
            addVertex(fx+1.f, fy,     fz,       1, 0,       0.f, 0.f, -1.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 1,       0.f, 0.f, -1.f);
            addVertex(fx,     fy+1.f, fz,       0, 1,       0.f, 0.f, -1.f);
            vSize = vertices.size()/3;
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
    }
    
    void addVertex(float posX, float posY, float posZ, float texU, float texV, float normX, float normY, float normZ){
        vertices.push_back(posX);
        vertices.push_back(posY);
        vertices.push_back(posZ);
        
        texCoord.push_back(texU);
        texCoord.push_back(texV);
        
        normals.push_back(normX);
        normals.push_back(normY);
        normals.push_back(normZ);
    }
    
    void addFace(uint v1, uint v2, uint v3, uint v4){
        faces.push_back(v1);
        faces.push_back(v2);
        faces.push_back(v3);
        
        faces.push_back(v1);
        faces.push_back(v3);
        faces.push_back(v4);
    }
    
    std::vector<float> vertices;
    std::vector<float> texCoord;
    std::vector<float> normals;
    std::vector<uint> faces;
};

template<std::size_t sizeX, std::size_t sizeY, std::size_t sizeZ>
class VoxelChunk
{
public:
    typedef VoxelChunk<sizeX, sizeY, sizeZ> Self;
    typedef VoxelChunkGrid<sizeX, sizeY, sizeZ> MyGrid;
    
    void generateGrid(){
        for(std::size_t y(0); y<MyGrid::SIZE_Y; ++y){
            for(std::size_t z(0); z<MyGrid::SIZE_Z; ++z){
                for(std::size_t x(0); x<MyGrid::SIZE_X; ++x){
                    if(x+5>y){
                        if(y==MyGrid::SIZE_Y-1){
                            mGrid.at(x, y, z) = VoxelType::GRASS;
                        }else if(y>MyGrid::SIZE_X/2){
                            mGrid.at(x, y, z) = VoxelType::DIRT;
                        }else{
                            mGrid.at(x, y, z) = VoxelType::STONE;
                        }
                    }else{
                        mGrid.at(x, y, z) = VoxelType::AIR;
                    }
                }
            }
        }
    }
    
    void generateMesh(){
        VoxelChunkMesh<MyGrid> voxMeshStone(mGrid, VoxelType::STONE);
        createMesh(&mMeshStone,
               voxMeshStone.getVerticesSize(),
               voxMeshStone.getPositions(),
               voxMeshStone.getTexCoord(),
               voxMeshStone.getNormal(),
               voxMeshStone.getIndexSize(),
               voxMeshStone.getFaces());
        
        VoxelChunkMesh<MyGrid> voxMeshDirt(mGrid, VoxelType::DIRT);
        createMesh(&mMeshDirt,
               voxMeshDirt.getVerticesSize(),
               voxMeshDirt.getPositions(),
               voxMeshDirt.getTexCoord(),
               voxMeshDirt.getNormal(),
               voxMeshDirt.getIndexSize(),
               voxMeshDirt.getFaces());
        
        VoxelChunkMesh<MyGrid> voxMeshGrass(mGrid, VoxelType::GRASS);
        createMesh(&mMeshGrass,
               voxMeshGrass.getVerticesSize(),
               voxMeshGrass.getPositions(),
               voxMeshGrass.getTexCoord(),
               voxMeshGrass.getNormal(),
               voxMeshGrass.getIndexSize(),
               voxMeshGrass.getFaces());
    }
    
    void loadTexture(){
        GraphicsWrapper::createTexture(&mTextureStone, "../data/stone.dds");
        GraphicsWrapper::createTexture(&mTextureDirt, "../data/dirt.dds");
        GraphicsWrapper::createTexture(&mTextureGrass, "../data/grass.dds");
    }
    
    void draw(const glm::mat4& MVP, const GraphicsWrapper::Shader& shader){
        GraphicsWrapper::setTexture(&mTextureStone, &shader);
        GraphicsWrapper::drawMesh(&mMeshStone, MVP, shader);
        GraphicsWrapper::setTexture(&mTextureDirt, &shader);
        GraphicsWrapper::drawMesh(&mMeshDirt, MVP, shader);
        GraphicsWrapper::setTexture(&mTextureGrass, &shader);
        GraphicsWrapper::drawMesh(&mMeshGrass, MVP, shader);
    }
    
    void unload(){
        GraphicsWrapper::destroyMesh(&mMeshStone);
        GraphicsWrapper::destroyTexture(&mTextureStone);
    }
    
private:
    MyGrid mGrid;
    GraphicsWrapper::Mesh mMeshStone;
    GraphicsWrapper::Mesh mMeshDirt;
    GraphicsWrapper::Mesh mMeshGrass;
    GraphicsWrapper::Texture mTextureStone;
    GraphicsWrapper::Texture mTextureDirt;
    GraphicsWrapper::Texture mTextureGrass;
};
