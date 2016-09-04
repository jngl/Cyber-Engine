#include "Renderer.hpp"

#include <fstream>
#include <vector>

math::Matrix4f currentViewMatrix;
math::Matrix4f currentProjectionMatrix;

namespace Renderer
{    
    //render
    void createRenderer(){
        glEnable(GL_DEPTH_TEST);
        
        glViewport(0,0,800,600);
    }
    
    void destroyRenderer(){
    }
    
    //view
    void setViewMatrix(math::Matrix4f m){
        currentViewMatrix = m;
    }
    
    //projection
    void setProjectionMatrix(math::Matrix4f m){
        currentProjectionMatrix = m;
    }
    
    //Mesh
    void createMesh (Mesh* mesh,
                     unsigned int nbVertices,
                     float* vertices,
                     unsigned int nbFaces,
                     unsigned int* faces
                    )
    {
        glGenBuffers(2, mesh->id);
        
        mesh->nbFaces = nbFaces;
        
        // vertices
        glBindBuffer(GL_ARRAY_BUFFER,
                     mesh->id[0]); 
        glBufferData(GL_ARRAY_BUFFER,
                     nbVertices*3*sizeof(float),
                     vertices,
                     GL_STATIC_DRAW);
  
        // indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                     mesh->id[1]); 
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     nbFaces*3*sizeof(unsigned int),
                     faces,
                     GL_STATIC_DRAW);
        
    }
    void destroyMesh(Mesh* mesh){ 
        glDeleteBuffers(2,mesh->id);
    }
    void drawMesh   (Mesh* mesh, math::Matrix4f m){
        glMatrixMode(GL_MODELVIEW);
        math::Matrix4f mv = currentViewMatrix * m;
        glLoadMatrixf(mv.m);
        
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(currentProjectionMatrix.m);
        
        glBindBuffer(GL_ARRAY_BUFFER,mesh->id[0]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->id[1]);
        glDrawElements(GL_TRIANGLES,
                       mesh->nbFaces,
                       GL_UNSIGNED_INT,
                       (void *)0);

        glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
    
    //shader
    
    void checkCompilation(GLuint shaderId) {
        // check if the compilation was successfull (and display syntax errors)
        // call it after each shader compilation
        GLint result = GL_FALSE;
        int infoLogLength;

        glGetShaderiv(shaderId,GL_COMPILE_STATUS,&result);
        glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        
        if(infoLogLength>0) {
            std::vector<char> message(infoLogLength+1);
            glGetShaderInfoLog(shaderId,infoLogLength,NULL,&message[0]);
            printf("%s\n", &message[0]);
        }
    }

   void checkLinks(GLuint programId) {
        // check if links were successfull (and display errors)
        // call it after linking the program  
        GLint result = GL_FALSE;
        int infoLogLength;

        glGetProgramiv(programId,GL_LINK_STATUS,&result);
        glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength);
        
        if(infoLogLength>0) {
            std::vector<char> message(infoLogLength+1);
            glGetProgramInfoLog(programId,infoLogLength,NULL,&message[0]);
            printf("%s\n", &message[0]);
        }
    }

    std::string getCode(const char *file_path) {
        // return a string containing the source code of the input file
        std::string   shaderCode;
        std::ifstream shaderStream(file_path,std::ios::in);

        if(!shaderStream.is_open()) {
            cout << "Unable to open " << file_path << endl;
            return "";
        }

        std::string line = "";
        while(getline(shaderStream,line))
            shaderCode += "\n" + line;
        shaderStream.close();
        
        return shaderCode;
    }
        
    void createShader(ShaderId& shader, std::string vert, std::string frag){
        // create and compile vertex shader object
        std::string vertexCode   = getCode(vert.c_str());
        const char * vertexCodeC = vertexCode.c_str();
        GLuint vertexId   = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexId,1,&(vertexCodeC),NULL);
        glCompileShader(vertexId);
        checkCompilation(vertexId);

        // create and compile fragment shader object
        std::string fragmentCode = getCode(frag.c_str());
        const char * fragmentCodeC = fragmentCode.c_str();
        GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentId,1,&(fragmentCodeC),NULL);
        glCompileShader(fragmentId);
        checkCompilation(fragmentId);

        // create, attach and link program object
        shader = glCreateProgram();
        glAttachShader(shader,vertexId);
        glAttachShader(shader,fragmentId);
        glLinkProgram(shader);
        checkLinks(shader);

        // delete vertex and fragment ids
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
    }
    
    void destroyShade(ShaderId& shader){
        if(glIsProgram(shader)) {
            glDeleteProgram(shader);
        }
    }
    
    void setShader(ShaderId& shader){
        glUseProgram(shader);
    }
}
