#pragma once

#include <glad/glad.h>

#include <string>

#include <glm/mat4x4.hpp>


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
                     const Shader& shader);
}
