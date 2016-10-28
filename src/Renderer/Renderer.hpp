#pragma once

#include <glad/glad.h>

#include <string>

#include <glm/mat4x4.hpp>

namespace Renderer
{
    //render
    void createRenderer();
    void destroyRenderer();
    
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
    void setTexture     (Texture* t, Shader* s);
    
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
                     glm::mat4 mvp,
                     Shader& shader);
    
    //FrameBuffer
    struct FrameBuffer;
    
    void createFrameBuffer  (FrameBuffer* fb);
    void destroyFrameBuffer (FrameBuffer* fb);
    void setFrameBuffer     (FrameBuffer* fb);
}
