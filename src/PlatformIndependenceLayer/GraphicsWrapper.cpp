#include "GraphicsWrapper.hpp"

#include "../Core/Error.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>

#define GL_DEBUG

#ifdef GL_DEBUG
	#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
	#define glCheck(call) (call)
#endif

void glCheckError(const std::string& file, unsigned int line){
    // Get the last error
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR)
    {
        std::string error = "unknown error";
        std::string description  = "no description";

        // Decode the error code
        switch (errorCode)
        {
            case GL_INVALID_ENUM :
            {
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case GL_INVALID_VALUE :
            {
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;
            }

            case GL_INVALID_OPERATION :
            {
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;
            }

            /*case GL_STACK_OVERFLOW :
            {
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;
            }

            case GL_STACK_UNDERFLOW :
            {
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;
            }*/

            case GL_OUT_OF_MEMORY :
            {
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION :
            {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
                description = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
                break;
            }
        }

        //std::cout<<"Warning OpenGL in \""<<file<<"\" (l"<<line<<") : "<<error<<" ; "<<description<<std::endl;

        throw core::Error(std::string("An internal OpenGL call failed in ")+file+" ( "+std::to_string(line)+" ) : "+error+", "+description);
    }
}

namespace GraphicsWrapper
{    
    //render
    void constructGraphicsWrapper(){
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
    
        
        glCheck(glEnable(GL_DEPTH_TEST));
        
        glCheck(glViewport(0,0,800,600));
    }
    
    void destructGraphicsWrapper(){
    }
    
    //Buffer
    void createBuffer(Buffer* buffer, BufferType type, BufferDataType dataType, int size, int nbBlock, const void* data){
        buffer->size = size;
        buffer->nbBlock = nbBlock;
        
        if(type == BufferType::VERTEX_ATTRIBUTE){
            buffer->target = GL_ARRAY_BUFFER;
        }else{
            buffer->target = GL_ELEMENT_ARRAY_BUFFER;
        }
        
        int typeSize;
        if(dataType == BufferDataType::FLOAT){
            typeSize = sizeof(float);
            buffer->typeGL = GL_FLOAT;
        }else{
            typeSize = sizeof(unsigned int);
            buffer->typeGL = GL_UNSIGNED_INT;
        }
        
        glCheck(glGenBuffers(1, &buffer->id));
        glCheck(glBindBuffer(buffer->target,
                    buffer->id)); 
        glCheck(glBufferData(buffer->target,
                     typeSize*size*nbBlock,
                     data,
                     GL_STATIC_DRAW));
    }
    
    void destroyBuffer(Buffer* buffer){
        glCheck(glDeleteBuffers(1, &buffer->id));
    }
    
    void drawBuffer( std::initializer_list<Buffer*> list ){
        int i(0);
        for( auto elem : list )
        {
            if(elem->target==GL_ARRAY_BUFFER){
                glCheck(glEnableVertexAttribArray(i));
                glCheck(glBindBuffer(GL_ARRAY_BUFFER, elem->id));
                glCheck(glVertexAttribPointer(
                    i,                  // attribute
                    elem->size,                  // size
                    elem->typeGL,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                ));
            }else{
                glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elem->id));
                glCheck(glDrawElements(GL_TRIANGLES,
                            elem->nbBlock*3,
                            elem->typeGL,
                            (void *)0));          
            
                for(int j(i-1); j>=0; --j){
                    glCheck(glDisableVertexAttribArray(j));
                }
            }
            ++i;
        }
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
        mesh->nbFaces = nbFaces;
        
        createBuffer(&mesh->buffer[0], BufferType::VERTEX_ATTRIBUTE, BufferDataType::FLOAT, 3, nbVertices, vertices);
        createBuffer(&mesh->buffer[1], BufferType::VERTEX_ATTRIBUTE, BufferDataType::FLOAT, 2, nbVertices, texCoord);
        createBuffer(&mesh->buffer[2], BufferType::VERTEX_ATTRIBUTE, BufferDataType::FLOAT, 3, nbVertices, normals);
        createBuffer(&mesh->buffer[3], BufferType::VERTEX_ARRAY_INDICES, BufferDataType::UNSIGNED_INT, 3, nbFaces, faces);        
    }
    void destroyMesh(Mesh* mesh){ 
        destroyBuffer(&mesh->buffer[0]);
        destroyBuffer(&mesh->buffer[1]);
        destroyBuffer(&mesh->buffer[2]);
        destroyBuffer(&mesh->buffer[3]);
    }
    void drawMesh   (Mesh* mesh, 
                     glm::mat4 mvp,
                     const Shader& shader){
        
        glCheck(glUseProgram(shader.id));
        glCheck(glUniformMatrix4fv(shader.GBuffersMdvMatLoc,1,GL_FALSE,glm::value_ptr(mvp)));
        
        drawBuffer({&mesh->buffer[0], &mesh->buffer[1], &mesh->buffer[2], &mesh->buffer[3]});
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
    
    void destroyShader(Shader& shader){
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
    
    void setTexture (Texture* t, const Shader* s){
        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->id);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(s->texture, 0);
    }
}
