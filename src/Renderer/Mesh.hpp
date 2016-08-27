#pragma once

#include <GL/glew.h>

#include "MeshData.hpp"

class Mesh
{
public:
	Mesh(MeshData& data);
	~Mesh();
	
	void draw();
	
private:
	GLuint makeBuffer(GLenum target,const void *buffer_data,GLsizei buffer_size);
	
	 GLuint vertexBuffer, texCoordBuffer, elementBuffer;
	 
	 int nbrElement;
};
