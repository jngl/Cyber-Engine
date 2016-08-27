#include "MeshData.hpp"

unsigned short MeshData::addVertex(math::Vec3f pos,
                                   math::Vec2f ptexCoord)
{
	vertices.push_back(pos);
	texCoord.push_back(ptexCoord);
	return vertices.size()-1;
}
void MeshData::addFace(unsigned short p1, 
                           unsigned short p2,
                           unsigned short p3)
{
	elements.push_back((unsigned short)p1);
	elements.push_back((unsigned short)p2);
	elements.push_back((unsigned short)p3);
}
void MeshData::addFace(unsigned short p1, 
                           unsigned short p2,
                           unsigned short p3,
                           unsigned short p4)
{
	elements.push_back((unsigned short)p1);
	elements.push_back((unsigned short)p2);
	elements.push_back((unsigned short)p3);
	
	elements.push_back((unsigned short)p1);
	elements.push_back((unsigned short)p3);
	elements.push_back((unsigned short)p4);
}

void MeshData::makeCube(){
    //sides
	unsigned short p1=addVertex(math::Vec3f(-0.5f,-0.5f,0.5f),
                                math::Vec2f(0.0f,0.0f));
	unsigned short p2=addVertex(math::Vec3f(-0.5f,0.5f,0.5f),
                                math::Vec2f(0.0f,1.0f));
	unsigned short p3=addVertex(math::Vec3f(0.5f,0.5f,0.5f),
                                math::Vec2f(1.0f,1.0f));
	unsigned short p4=addVertex(math::Vec3f(0.5f,-0.5f,0.5f),
                                math::Vec2f(1.0f,0.0f));
	
	unsigned short p5=addVertex(math::Vec3f(-0.5f,-0.5f,-0.5f),
                                math::Vec2f(1.0f,0.0f));
	unsigned short p6=addVertex(math::Vec3f(-0.5f,0.5f,-0.5f),
                                math::Vec2f(1.0f,1.0f));
	unsigned short p7=addVertex(math::Vec3f(0.5f,0.5f,-0.5f),
                                math::Vec2f(0.0f,1.0f));
	unsigned short p8=addVertex(math::Vec3f(0.5f,-0.5f,-0.5f),
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
