#pragma once

#include <glad/glad.h>

#include <string>

#include "../Math/Matrix4.hpp"

namespace Renderer
{
    //render
    void createRenderer();
    void destroyRenderer();
    
    //Texture
    struct Texture;
    
    void createTexture  (Texture* t,std::string file);
    void destroyTexture (Texture* t);
    void setTexture     (Texture* t);
    
    //Shader
    struct Shader
    {
        GLuint id;
        GLuint GBuffersMdvMatLoc;
    };
    
    void createShader   (Shader& s, std::string vert, std::string frag);
    void destroyShader  (Shader& s);
    
    //Mesh
    struct Mesh{
        GLuint id[4];
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
                     math::Matrix4f mvp,
                     Shader& shader);
    
    //FrameBuffer
    struct FrameBuffer;
    
    void createFrameBuffer  (FrameBuffer* fb);
    void destroyFrameBuffer (FrameBuffer* fb);
    void setFrameBuffer     (FrameBuffer* fb);
}
