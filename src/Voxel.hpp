#pragma once

#include <array>
#include <vector>
#include <cstddef>
#include <iostream>

#include "Core/Error.hpp"

enum class VoxelType
{
    AIR,
    STONE
};

template<std::size_t sizeX, std::size_t sizeY, std::size_t sizeZ>
class VoxelChunk
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
    VoxelChunkMesh(MyVoxelChunk& voxels)
    {
        for(std::size_t y(0); y<MyVoxelChunk::SIZE_Y; ++y){
            for(std::size_t z(0); z<MyVoxelChunk::SIZE_Z; ++z){
                for(std::size_t x(0); x<MyVoxelChunk::SIZE_X; ++x){
                    if(voxels.at(x, y, z)!=VoxelType::AIR){
                        gennerateCube(voxels, x, y, z);
                    }
                }
            }
        }
        std::cout<<" "<<vertices.size()<<std::endl;
        std::cout<<" "<<texCoord.size()<<std::endl;
        std::cout<<" "<<normals.size()<<std::endl;
        std::cout<<" "<<faces.size()<<std::endl;
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


