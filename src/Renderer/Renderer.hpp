#pragma once

#include <string>
#include <GL/glew.h>

#include "../Math/Matrix4.hpp"

namespace Renderer
{
    //render
    void createRenderer();
    void destroyRenderer();
    
    //view
    void setViewMatrix(math::Matrix4f m);
    
    //projection
    void setProjectionMatrix(math::Matrix4f m);
    
    //Mesh
    struct Mesh{
        GLuint id[2];
        unsigned int nbFaces;
    };
    
    void createMesh (Mesh* mesh,
                     unsigned int nbVertices,
                     float* vertices,
                     unsigned int nbFaces,
                     unsigned int* faces
                    );
    void destroyMesh(Mesh* mesh);
    void drawMesh   (Mesh* mesh, math::Matrix4f m);
    
    //Texture
    struct Texture;
    
    void createTexture  (Texture* t,std::string file);
    void destroyTexture (Texture* t);
    void setTexture     (Texture* t);
    
    //Shader
    typedef GLuint ShaderId;
    
    void createShader   (ShaderId& s, std::string vert, std::string frag);
    void destroyShader  (ShaderId& s);
    void setShader      (ShaderId& s);
    //todo add param
    
    //FrameBuffer
    struct FrameBuffer;
    
    void createFrameBuffer  (FrameBuffer* fb);
    void destroyFrameBuffer (FrameBuffer* fb);
    void setFrameBuffer     (FrameBuffer* fb);
}
