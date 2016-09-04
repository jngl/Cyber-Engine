#pragma once

#include <vector>

#include "../Math/Vector3.hpp"

struct MeshData
{
    std::vector<math::Vec3f> vertices;
	std::vector<math::Vec2f> texCoord;
	std::vector<unsigned int> elements;
    
    unsigned int addVertex(math::Vec3f pos, 
                             math::Vec2f ptexCoord);
	
	void addFace(unsigned int p1, 
                 unsigned int p2, 
                 unsigned int p3);
    
	void addFace(unsigned int p1,
                 unsigned int p2, 
                 unsigned int p3, 
                 unsigned int p4);
    
    void makeCube();
};
