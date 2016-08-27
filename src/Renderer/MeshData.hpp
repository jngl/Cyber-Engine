#pragma once

#include <vector>

#include "../Math/Vector3.hpp"

struct MeshData
{
    std::vector<math::Vec3f> vertices;
	std::vector<math::Vec2f> texCoord;
	std::vector<unsigned short> elements;
    
    unsigned short addVertex(math::Vec3f pos, 
                             math::Vec2f ptexCoord);
	
	void addFace(unsigned short p1, 
                 unsigned short p2, 
                 unsigned short p3);
    
	void addFace(unsigned short p1,
                 unsigned short p2, 
                 unsigned short p3, 
                 unsigned short p4);
    
    void makeCube();
};
