#include "System.hpp"

#include "Core/Error.hpp"
#include "Core/Modules.hpp"

#include "PlatformIndependenceLayer/GraphicsWrapper.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include <SDL_main.h>

template<class T>
class Vector2D
{
public:
	Vector2D() :
		mSizeX(0),
		mSizeY(0)
	{

	}

	std::size_t sizeX() {
		return mSizeX;
	}
	std::size_t sizeY() {
		return mSizeY;
	}

	void create(std::size_t x, std::size_t y) {
		mData.resize(x*y);
	}

	void destroy() {
		mData.resize(0);
	}

	T& at(std::size_t x, std::size_t y) {
		return mData.at(y*mSizeX + x);
	}

private:
	std::vector<T> mData;
	std::size_t mSizeX;
	std::size_t mSizeY;
};

unsigned int nbVertices = 4;
const float vertices[] = {-0.5f, -0.5f, 0.f,
                                        0.5, -0.5, 0.f,
                                        0.5, 0.5, 0.f,
                                        -0.5, 0.5, 0.f
};
const float texCoord[] = {-0.5f, -0.5f, 0.f,
                                        0.5, -0.5,
                                        0.5, 0.5,
                                        -0.5, 0.5
};
const float normals[] = {0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f
};
unsigned int nbFaces = 2;
const unsigned int faces[] = { 2, 1, 0,  2, 0, 3};

enum class Piece
{
	PLAYER,
	FIRE,
	WATER,
	DIRT,
	AIR,
	DARK,
	LIGHT,
};

extern "C"
int main(int argc, char *argv[]){
     try{
        Modules::constructAllModules();
        
        GraphicsWrapper::Mesh mesh;
        GraphicsWrapper::createMesh(&mesh,
                nbVertices,
                vertices,
                texCoord,
                normals,
                nbFaces,
                faces
        );
        
        GraphicsWrapper::Shader shader;
        GraphicsWrapper::createShader(shader,
                 "../data/shaders/noLight.vert",
                 "../data/shaders/noLight.frag");
        
        GraphicsWrapper::Texture tex;
        GraphicsWrapper::createTexture(&tex, "../data/stone.dds");

        GraphicsWrapper::setTexture(&tex, &shader);
        
        glm::mat4 model(1.0f);
        
        glm::mat4 view (1.0f);
         
        glm::mat4 proj = glm::ortho(-0.5f, 0.5f,
                                                        -0.5f, 0.5f,
                                                        -100.f, 100.f);

		Vector2D<Piece> board;

        
        while(System::isRunning()){
            System::doEvent();
            System::clear();
            
            glm::mat4 MVP = proj * view * model;
            GraphicsWrapper::drawMesh(&mesh, MVP, shader);
            
            System::endFrame();
        }
        
        GraphicsWrapper::destroyShader(shader);
        GraphicsWrapper::destroyMesh(&mesh);   
        
        Modules::destructAllModules();
        return 0;
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
