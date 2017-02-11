#pragma once

#include "BoxelChunkGrid.hpp"

template<class MyBoxelChunk>
class BoxelChunkMesh
{
public:
    BoxelChunkMesh(MyBoxelChunk& boxels, BoxelType type)
    {
        for(unsigned int y(0); y<MyBoxelChunk::SIZE_Y; ++y){
            for(unsigned int z(0); z<MyBoxelChunk::SIZE_Z; ++z){
                for(unsigned int x(0); x<MyBoxelChunk::SIZE_X; ++x){
                    if(boxels.at(x, y, z)==type){
                        gennerateCube(boxels, x, y, z);
                    }
                }
            }
        }
    }
    
	unsigned int getVerticesSize(){
        return static_cast<unsigned int>(vertices.size()/3);
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
    
	unsigned int getIndexSize(){
        return static_cast<unsigned int>(faces.size());
    }
    
    unsigned int* getFaces(){
        return &faces[0];
    }
    
private:
    void gennerateCube(MyBoxelChunk& boxels, unsigned int x, unsigned int y, unsigned int z){
        float fx = static_cast<float>(x);
        float fy = static_cast<float>(y);
        float fz = static_cast<float>(z);
        
		unsigned int vSize;
        
        //up
        if( y+1==MyBoxelChunk::SIZE_Y || boxels.at(x,y+1,z)==BoxelType::AIR ){
            addVertex(fx,     fy+1.f, fz,       0, 0,       0.f, 1.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 0,       0.f, 1.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,   1, 1,       0.f, 1.f, 0.f);
            addVertex(fx,     fy+1.f, fz+1.f,   0, 1,       0.f, 1.f, 0.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
       
        //down
        if( y==0 || boxels.at(x,y-1,z)==BoxelType::AIR ){
            addVertex(fx,     fy, fz,       0, 0,       0.f, -1.f, 0.f);
            addVertex(fx+1.f, fy, fz,       1, 0,       0.f, -1.f, 0.f);
            addVertex(fx+1.f, fy, fz+1.f,   1, 1,       0.f, -1.f, 0.f);
            addVertex(fx,     fy, fz+1.f,   0, 1,       0.f, -1.f, 0.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //left
        if( x+1==MyBoxelChunk::SIZE_X || boxels.at(x+1,y,z)==BoxelType::AIR ){
            addVertex(fx+1.f, fy,     fz,       0, 0,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 0,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,   1, 1,       1.f, 0.f, 0.f);
            addVertex(fx+1.f, fy,     fz+1.f,   0, 1,       1.f, 0.f, 0.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //right
        if( x==0 || boxels.at(x-1,y,z)==BoxelType::AIR ){
            addVertex(fx, fy,     fz,       0, 0,       -1.f, 0.f, 0.f);
            addVertex(fx, fy+1.f, fz,       1, 0,       -1.f, 0.f, 0.f);
            addVertex(fx, fy+1.f, fz+1.f,   1, 1,       -1.f, 0.f, 0.f);
            addVertex(fx, fy,     fz+1.f,   0, 1,       -1.f, 0.f, 0.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //front
        if( z+1==MyBoxelChunk::SIZE_Z || boxels.at(x,y,z+1)==BoxelType::AIR ){
            addVertex(fx,     fy,     fz+1.f,       0, 0,       0.f, 0.f, 1.f);
            addVertex(fx+1.f, fy,     fz+1.f,       1, 0,       0.f, 0.f, 1.f);
            addVertex(fx+1.f, fy+1.f, fz+1.f,       1, 1,       0.f, 0.f, 1.f);
            addVertex(fx,     fy+1.f, fz+1.f,       0, 1,       0.f, 0.f, 1.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
            addFace(vSize-4, vSize-3, vSize-2, vSize-1);
        }
        
        //back
        if( z==0 || boxels.at(x,y,z-1)==BoxelType::AIR ){
            
            addVertex(fx,     fy,     fz,       0, 0,       0.f, 0.f, -1.f);
            addVertex(fx+1.f, fy,     fz,       1, 0,       0.f, 0.f, -1.f);
            addVertex(fx+1.f, fy+1.f, fz,       1, 1,       0.f, 0.f, -1.f);
            addVertex(fx,     fy+1.f, fz,       0, 1,       0.f, 0.f, -1.f);
            vSize = static_cast<unsigned int>(vertices.size()/3);
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
    
    void addFace(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4){
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
    std::vector<unsigned int> faces;
}; 
