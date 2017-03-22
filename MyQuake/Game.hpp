#pragma once

#include "Draw.hpp"
#include "Rect.hpp"

#include <SDL.h>

class Engine;

class Game
{
public:
	Game(Engine* engine);
	~Game();
	
	void update(float time);
	void draw();
	void onKeyboardEvent(SDL_KeyboardEvent& event);
	
private:
	Engine* mEngine;
	bool mActionMoveUp;
	bool mActionMoveDown;
	bool mActionMoveLeft;
	bool mActionMoveRight;
	Rectf mPlayer;
	Rectf mRock;
};
