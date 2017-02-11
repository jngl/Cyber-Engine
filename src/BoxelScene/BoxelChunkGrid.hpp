#pragma once

#include "BoxelType.hpp"

#include "Core/Error.hpp"

#include <array>

template<   unsigned int sizeX,
	    unsigned int sizeY,
	    unsigned int sizeZ>
class BoxelChunkGrid
{
public:
    static const unsigned int SIZE_X = sizeX;
    static const unsigned int SIZE_Y = sizeY;
    static  const unsigned int SIZE_Z = sizeZ;
    
    BoxelType& at(unsigned int x, unsigned int y, unsigned int z){
        coreCheckParam(x<sizeX && y<sizeY && z<sizeZ);
        
        return boxels[y*sizeX*sizeZ + z*sizeX + x];
    }
    
private:
    std::array<BoxelType, sizeX*sizeY*sizeZ> boxels;
};
