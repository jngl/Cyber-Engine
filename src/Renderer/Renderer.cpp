#include "Renderer.hpp"

#include "GLDebug.hpp"
#include "CubeData.hpp"

#include "../Core/Error.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>

namespace Renderer
{    
    //render
    void createRenderer(){
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
    
        
        glCheck(glEnable(GL_DEPTH_TEST));
        
        glCheck(glViewport(0,0,800,600));
    }
    
    void destroyRenderer(){
    }
    
    //Mesh
    void createMesh (Mesh* mesh,
                     unsigned int nbVertices,
                     const float* vertices,
                     const float* texCoord,
                     const float* normals,
                     unsigned int nbFaces,
                     const unsigned int* faces
                    )
    {
        glCheck(glGenBuffers(4, mesh->id));
        
        mesh->nbFaces = nbFaces;
        
        // vertices
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,
                     mesh->id[0])); 
        glCheck(glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float)*3*nbVertices,
                     vertices,
                     GL_STATIC_DRAW));
        
        //texCoord
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,
                     mesh->id[1])); 
        glCheck(glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float)*2*nbVertices,
                     texCoord,
                     GL_STATIC_DRAW));
        
        //normal
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,
                     mesh->id[2])); 
        glCheck(glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float)*3*nbVertices,
                     normals,
                     GL_STATIC_DRAW));
  
        // indices
        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                     mesh->id[3])); 
        glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(unsigned int) * nbFaces,
                     faces,
                     GL_STATIC_DRAW));
        
    }
    void destroyMesh(Mesh* mesh){ 
        glCheck(glDeleteBuffers(2,mesh->id));
    }
    void drawMesh   (Mesh* mesh, 
                     glm::mat4 mvp,
                     Shader& shader){
        
        glCheck(glUseProgram(shader.id));
        glCheck(glUniformMatrix4fv(shader.GBuffersMdvMatLoc,1,GL_FALSE,glm::value_ptr(mvp)));
        
        //vertex
        glCheck(glEnableVertexAttribArray(0));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, mesh->id[0]));
		glCheck(glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		));
        
        //texCoord
        glCheck(glEnableVertexAttribArray(1));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,mesh->id[1]));
        glCheck(glVertexAttribPointer(
                              1,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0));
        
        //normal
        glCheck(glEnableVertexAttribArray(2));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER,mesh->id[2]));
        glCheck(glVertexAttribPointer(
                              2,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0));

        //index
        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh->id[3]));
        glCheck(glDrawElements(GL_TRIANGLES,
                       mesh->nbFaces,
                       GL_UNSIGNED_INT,
                       (void *)0));          
    
        glCheck(glDisableVertexAttribArray(0));
		glCheck(glDisableVertexAttribArray(1));
		glCheck(glDisableVertexAttribArray(2));
    }
    
    //shader
    
    void checkCompilation(GLuint shaderId) {
        // check if the compilation was successfull (and display syntax errors)
        // call it after each shader compilation
        GLint result = GL_FALSE;
        int infoLogLength(0);

        glCheck(glGetShaderiv(shaderId,GL_COMPILE_STATUS,&result));
        glCheck(glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&infoLogLength));
        
        if(!result && infoLogLength>0) {
            std::vector<char> message(infoLogLength+1);
            glCheck(glGetShaderInfoLog(shaderId,infoLogLength,NULL,&message[0]));
            throw core::Error(std::string("GLSL code error : ")+&message[0]);
        }
    }

   void checkLinks(GLuint programId) {
        // check if links were successfull (and display errors)
        // call it after linking the program  
        GLint result = GL_FALSE;
        int infoLogLength;

        glCheck(glGetProgramiv(programId,GL_LINK_STATUS,&result));
        glCheck(glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength));
        
        if(!result && infoLogLength>0) {
            std::vector<char> message(infoLogLength+1);
            glCheck(glGetProgramInfoLog(programId,infoLogLength,NULL,&message[0]));
            
            throw core::Error(std::string("GLSL link error : ")+&message[0]);
        }
    }

    std::string getCode(const char *file_path) {
        // return a string containing the source code of the input file
        std::string   shaderCode;
        std::ifstream shaderStream(file_path,std::ios::in);

        if(!shaderStream.is_open()) {
            std::cerr << "Unable to open " << file_path << std::endl;
            return "";
        }

        std::string line = "";
        while(getline(shaderStream,line))
            shaderCode += "\n" + line;
        shaderStream.close();
        
        return shaderCode;
    }
        
    void createShader(Shader& shader, std::string vert, std::string frag){
        // create and compile vertex shader object
        std::string vertexCode   = getCode(vert.c_str());
        const char * vertexCodeC = vertexCode.c_str();
        GLuint vertexId   = glCreateShader(GL_VERTEX_SHADER);
        glCheck(glShaderSource(vertexId,1,&(vertexCodeC),NULL));
        glCheck(glCompileShader(vertexId));
        checkCompilation(vertexId);

        // create and compile fragment shader object
        std::string fragmentCode = getCode(frag.c_str());
        const char * fragmentCodeC = fragmentCode.c_str();
        GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        glCheck(glShaderSource(fragmentId,1,&(fragmentCodeC),NULL));
        glCheck(glCompileShader(fragmentId));
        checkCompilation(fragmentId);

        // create, attach and link program object
        glCheck(shader.id = glCreateProgram());
        glCheck(glAttachShader(shader.id,vertexId));
        glCheck(glAttachShader(shader.id,fragmentId));
        glCheck(glLinkProgram(shader.id));
        checkLinks(shader.id);

        // delete vertex and fragment ids
        glCheck(glDeleteShader(vertexId));
        glCheck(glDeleteShader(fragmentId));
        
        // location
        glCheck(glUseProgram(shader.id));
        glCheck(shader.GBuffersMdvMatLoc =
                glGetUniformLocation(shader.id,"MVP"));
        glCheck(shader.texture  = glGetUniformLocation(shader.id, "textureSampler"));
    }
    
    void destroyShade(Shader& shader){
        if(glIsProgram(shader.id)) {
            glDeleteProgram(shader.id);
        }
    }
    
    #define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
    #define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
    #define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
    
    void createTexture  (Texture* t,std::string file){
        unsigned char header[124]; 
 
        FILE *fp; 
    
        /* essaie d'ouvrir le fichier */ 
        fp = fopen(file.c_str(), "rb"); 
        if (fp == NULL) 
            throw core::Error(std::string("error with dds file"));
    
        /* vérifie le type du fichier */ 
        char filecode[4]; 
        fread(filecode, 1, 4, fp); 
        if (strncmp(filecode, "DDS ", 4) != 0) { 
            fclose(fp); 
            throw core::Error(std::string("error in dds file"));
        } 
    
        /* récupère la description de la surface */ 
        fread(&header, 124, 1, fp); 
    
        unsigned int height      = *(unsigned int*)&(header[8 ]); 
        unsigned int width         = *(unsigned int*)&(header[12]); 
        unsigned int linearSize     = *(unsigned int*)&(header[16]); 
        unsigned int mipMapCount = *(unsigned int*)&(header[24]); 
        unsigned int fourCC      = *(unsigned int*)&(header[80]);
        
            unsigned char * buffer; 
        unsigned int bufsize; 
        /* quelle va être la taille des données incluant les MIP maps ? */ 
        bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
        buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
        fread(buffer, 1, bufsize, fp); 
        /* fermer le pointeur de fichier */ 
        fclose(fp);
        
        
        unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
        unsigned int format; 
        switch(fourCC) 
        { 
        case FOURCC_DXT1: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
            break; 
        case FOURCC_DXT3: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
            break; 
        case FOURCC_DXT5: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
            break; 
        default: 
            free(buffer); 
            throw core::Error(std::string("unsupported dds format"));
        }
        
        // Crée une texture OpenGL
        GLuint textureID; 
        glGenTextures(1, &textureID); 
    
        // "Lie" la nouvelle texture : tous les futurs appels aux fonctions de texture vont modifier cette texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        
            
        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
        unsigned int offset = 0; 
    
        /* charge les MIP maps */ 
        for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
        { 
            unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 
                0, size, buffer + offset); 
    
            offset += size; 
            width  /= 2; 
            height /= 2; 
        } 
        free(buffer); 
    
        t->id = textureID;
    }
    
    void destroyTexture (Texture* t){
        glDeleteTextures(1, &(t->id));
    }
    
    void setTexture (Texture* t, Shader* s){
        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->id);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(s->texture, 0);
    }
}
