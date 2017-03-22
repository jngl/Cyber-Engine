#include "Engine.hpp"

#include "system.hpp"
#include "video.hpp"

#include <GL/gl.h>

Engine::Engine():
mVideo(mSystem, mGame),
mDraw(this),
mGame(this)
{
	mConsole.print("Engine init");
}

Engine::~Engine()
{
	mConsole.print("Engine shutdown");
}

void Engine::frame(float time)
{
	mVideo.sendEvent();
	
	mGame.update(time);
	mGame.draw();
	
	mVideo.update();
}

System & Engine::getSystem()
{
	return mSystem;
}

Console & Engine::getConsole()
{
	return mConsole;
}
Draw & Engine::getDraw()
{
	return mDraw;
}


