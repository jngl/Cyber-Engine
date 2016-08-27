#include "Mesh.hpp"


Mesh::Mesh(MeshData& data)
{
	nbrElement=data.elements.size();
	
	vertexBuffer = makeBuffer(GL_ARRAY_BUFFER, &data.vertices[0], sizeof(float)*data.vertices.size()*3);
	
	texCoordBuffer = makeBuffer(GL_ARRAY_BUFFER, &data.texCoord[0], sizeof(float)*data.texCoord.size()*2);
	
	elementBuffer = makeBuffer(GL_ELEMENT_ARRAY_BUFFER,&data.elements[0], sizeof(unsigned short)*nbrElement);
}
Mesh::~Mesh()
{
	
}
GLuint Mesh::makeBuffer(GLenum target,const void *buffer_data,GLsizei buffer_size)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
	return buffer;
}
void Mesh::draw()
{
	// Utilisation des données des buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexPointer( 3, GL_FLOAT, 3 * sizeof(float), 0);
	
	//texCoord
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glTexCoordPointer( 2, GL_FLOAT, 2 * sizeof(float), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	// Activation d'utilisation des tableaux
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	// Rendu de notre géométrie
	glDrawElements(GL_TRIANGLES, nbrElement, GL_UNSIGNED_SHORT, 0);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}
