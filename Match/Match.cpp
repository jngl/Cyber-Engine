#include "System.hpp"

#include "Core/Error.hpp"
#include "Core/Modules.hpp"

#include "Renderer/Renderer.hpp"

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

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
const float vertices[] = {0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f,
                                        1.f, 1.f, 0.f,
                                        1.f, 0.f, 0.f
};
const float texCoord[] = {0.f, 0.f,
                                        0.f, 1.f,
                                        1.f, 1.f,
                                        1.f, 0.f
};
const float normals[] = {0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f,
                                         0.f, 0.f, -1.f
};
unsigned int nbFaces = 2;
const unsigned int faces[] = { 0, 1, 2,  0, 2, 3};

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
        
         Renderer::Texture_handle tex = Renderer::createTexture("../data/match/dark.dds");
         Renderer::Material_handle mat = Renderer::createMaterial(tex);
         Renderer::Model_handle model = Renderer::createModel(nbVertices, vertices, texCoord, normals, nbFaces, faces, mat );
         Renderer::Object_handle obj = Renderer::createObject(model);
         Renderer::Camera_handle cam = Renderer::createCamera();
         Renderer::setActiveCamera(cam);
         Renderer::getCameraProjectionMatrixRef(cam).projectOrthographic(0.f, 800.f,
                                                                                                            0.f, 600.f,
                                                                                                            -100.f, 100.f);
         Renderer::getCameraViewMatrixRef(cam);
		Vector2D<Piece> board;
        
        Renderer::getObjectMatrixRef(obj).addScale(math::Vector3f{100.f, 100.f, 1.f});
        
        while(System::isRunning()){
            System::doEvent();
            System::clear();
            
            Renderer::renderObject(obj);
            
            System::endFrame();
        }
        
        Modules::destructAllModules();
        return 0;
    }catch(core::Error& e){
        std::cerr<<"Fatal error : "<<e.what()<<std::endl;
        return 1;
    }
}
