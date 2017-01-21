#pragma once

#include <glad/glad.h>

#include <string>

#include "Math/Matrix4.hpp"

namespace GraphicsWrapper
{
    //module
    void constructGraphicsWrapper();
    void destructGraphicsWrapper();
    
     //Shader
    struct Shader
    {
        GLuint id;
        GLuint GBuffersMdvMatLoc;
        GLuint texture;
    };
    
    void createShader   (Shader& s, std::string vert, std::string frag);
    void destroyShader  (Shader& s);
    
    //Texture
    struct Texture{
        GLuint id;
    };
    
    void createTexture  (Texture* t,std::string file);
    void destroyTexture (Texture* t);
    void setTexture     (Texture* t, const Shader* s);
    
    //Buffer
    enum class BufferDataType{
        FLOAT,
        UNSIGNED_INT
    };
    
    enum class BufferType{
        VERTEX_ATTRIBUTE,
        VERTEX_ARRAY_INDICES
    };
    
    struct Buffer{
        GLuint id;
        GLint size;
        GLint nbBlock;
        GLenum target;
        GLenum typeGL;
    };
    
    void createBuffer(Buffer* buffer, BufferType type, BufferDataType dataType, int size, int nbBlock, const void* data);
    void destroyBuffer(Buffer* buffer);
    
    void drawBuffer( std::initializer_list<Buffer*> list );
    
    //Mesh
    struct Mesh{
        Buffer buffer[4];
        unsigned int nbFaces;
    };
    
    void createMesh (Mesh* mesh,
                     unsigned int nbVertices,
                     const float* vertices,
                     const float* texCoord,
                     const float* normals,
                     unsigned int nbFaces,
                     const unsigned int* faces
                    );
    void destroyMesh(Mesh* mesh);
    void drawMesh   (Mesh* mesh, 
                     const math::Matrix4f mvp,
                     const Shader& shader);
}
