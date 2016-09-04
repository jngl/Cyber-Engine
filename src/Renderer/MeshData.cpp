#include "MeshData.hpp"

unsigned int MeshData::addVertex(math::Vec3f pos,
                                   math::Vec2f ptexCoord)
{
	vertices.push_back(pos);
	texCoord.push_back(ptexCoord);
	return vertices.size()-1;
}
void MeshData::addFace(unsigned int p1, 
                           unsigned int p2,
                           unsigned int p3)
{
	elements.push_back((unsigned int)p1);
	elements.push_back((unsigned int)p2);
	elements.push_back((unsigned int)p3);
}
void MeshData::addFace(unsigned int p1, 
                           unsigned int p2,
                           unsigned int p3,
                           unsigned int p4)
{
	elements.push_back((unsigned int)p1);
	elements.push_back((unsigned int)p2);
	elements.push_back((unsigned int)p3);
	
	elements.push_back((unsigned int)p1);
	elements.push_back((unsigned int)p3);
	elements.push_back((unsigned int)p4);
}

void MeshData::makeCube(){
    //sides
	unsigned int p1=addVertex(math::Vec3f(-0.5f,-0.5f,0.5f),
                                math::Vec2f(0.0f,0.0f));
	unsigned int p2=addVertex(math::Vec3f(-0.5f,0.5f,0.5f),
                                math::Vec2f(0.0f,1.0f));
	unsigned int p3=addVertex(math::Vec3f(0.5f,0.5f,0.5f),
                                math::Vec2f(1.0f,1.0f));
	unsigned int p4=addVertex(math::Vec3f(0.5f,-0.5f,0.5f),
                                math::Vec2f(1.0f,0.0f));
	
	unsigned int p5=addVertex(math::Vec3f(-0.5f,-0.5f,-0.5f),
                                math::Vec2f(1.0f,0.0f));
	unsigned int p6=addVertex(math::Vec3f(-0.5f,0.5f,-0.5f),
                                math::Vec2f(1.0f,1.0f));
	unsigned int p7=addVertex(math::Vec3f(0.5f,0.5f,-0.5f),
                                math::Vec2f(0.0f,1.0f));
	unsigned int p8=addVertex(math::Vec3f(0.5f,-0.5f,-0.5f),
                                math::Vec2f(0.0f,0.0f));
		
	addFace(p1,p2,p3,p4);
	addFace(p5,p6,p7,p8);
	addFace(p1,p2,p6,p5);
	addFace(p3,p4,p8,p7);
	
	//up
	p1=addVertex(math::Vec3f(0.5f,-0.5f,0.5f),
                 math::Vec2f(0.0f,0.0f));
	p2=addVertex(math::Vec3f(-0.5f,-0.5f,0.5f), 
                 math::Vec2f(1.0f,0.0f));
	p3=addVertex(math::Vec3f(-0.5f,-0.5f,-0.5f),
                 math::Vec2f(1.0f,1.0f));
	p4=addVertex(math::Vec3f(0.5f,-0.5f,-0.5f),
                 math::Vec2f(0.0f,1.0f));
	
	addFace(p1,p2,p3,p4);
	
	//down
	p1=addVertex(math::Vec3f(0.5f,0.5f,0.5f),
                 math::Vec2f(0.0f,0.0f));
	p2=addVertex(math::Vec3f(-0.5f,0.5f,0.5f),
                 math::Vec2f(1.0f,0.0f));
	p3=addVertex(math::Vec3f(-0.5f,0.5f,-0.5f),
                 math::Vec2f(1.0f,1.0f));
	p4=addVertex(math::Vec3f(0.5f,0.5f,-0.5f),
                 math::Vec2f(0.0f,1.0f));
	
	addFace(p1,p2,p3,p4);
}
