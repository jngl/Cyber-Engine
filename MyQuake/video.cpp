#include "video.hpp"

#include "system.hpp"

Video::Video(System& system, Game& game):
mSystem(system),
mGame(game)
{
	//WARNING Game not construct
	SDL_Init(SDL_INIT_VIDEO); 
	mWindow = SDL_CreateWindow("MyQuake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	mGLContext = SDL_GL_CreateContext(mWindow);
	SDL_GL_MakeCurrent(mWindow, mGLContext);
}

Video::~Video()
{
	SDL_GL_DeleteContext(mGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Video::sendEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				mSystem.exit();
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				mGame.onKeyboardEvent(e.key);
				break;
			default:
				break;
		}
	}
}

void Video::update()
{
	SDL_GL_SwapWindow(mWindow);
}
