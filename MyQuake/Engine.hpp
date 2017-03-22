#pragma once

#include "system.hpp"
#include "video.hpp"
#include "Console.hpp"
#include "Draw.hpp"
#include "Game.hpp"

class Engine
{
public:
	Engine();
	~Engine();
	
	void frame(float time);
	
	System& getSystem();
	Console& getConsole();
	Draw& getDraw();
	
private:
	System mSystem;
	Video mVideo;
	Console mConsole;
	Draw mDraw;
	Game mGame;
};
