#pragma once

#include "system.hpp"
#include "Game.hpp"

#include <SDL.h>

class Video
{
public:
	Video(System& system, Game& game);
	~Video();
	
	void update();
	void sendEvent();
	
private:
	SDL_Window* mWindow;
	SDL_GLContext mGLContext;
	System& mSystem;
	Game& mGame;
};
