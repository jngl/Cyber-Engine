#include "Game.hpp"

#include "Engine.hpp"

Game::Game(Engine* engine):
mActionMoveUp(false),
mActionMoveDown(false),
mActionMoveLeft(false),
mActionMoveRight(false)
{
	mEngine = engine;
	
	mPlayer.x = 100;
	mPlayer.y = 100;
	mPlayer.w = 50;
	mPlayer.h = 50;
	
	mRock.x = 100;
	mRock.y = 300;
	mRock.w = 50;
	mRock.h = 50;
}

Game::~Game()
{
}

void Game::update(float time)
{
	const float speed = 100;
	
	float mx = 0.f;
	float my = 0.f;
	
	if(mActionMoveUp){
		my+=time*speed;
	}
	if(mActionMoveDown){
		my-=time*speed;
	}
	if(mActionMoveLeft){
		mx-=time*speed;
	}
	if(mActionMoveRight){
		mx+=time*speed;
	}
	
	mPlayer.x += mx;
	mPlayer.y += my;
}

void Game::draw()
{
	mEngine->getDraw().clear(0.f, 0.3f, 0.7f);
	mEngine->getDraw().ortho(0, 800, 0, 600, -100, 100);
	
	mEngine->getDraw().setColor(0.f, 1.f, 0.f);
	mEngine->getDraw().rect(mPlayer);
	
	mEngine->getDraw().setTexture(0);
	mEngine->getDraw().setColor(0.3f, 0.3f, 0.3f);
	mEngine->getDraw().rect(mRock);
}

void Game::onKeyboardEvent(SDL_KeyboardEvent& event){
	if(event.repeat==false){
		if(event.type==SDL_KEYDOWN){
			if(event.keysym.scancode == SDL_SCANCODE_W){
				mActionMoveUp = true;
			}else if(event.keysym.scancode == SDL_SCANCODE_S){
				mActionMoveDown = true;
			}else if(event.keysym.scancode == SDL_SCANCODE_A){
				mActionMoveLeft = true;
			}else if(event.keysym.scancode == SDL_SCANCODE_D){
				mActionMoveRight = true;
			}
		}else{
			if(event.keysym.scancode == SDL_SCANCODE_W){
				mActionMoveUp = false;
			}else if(event.keysym.scancode == SDL_SCANCODE_S){
				mActionMoveDown = false;
			}else if(event.keysym.scancode == SDL_SCANCODE_A){
				mActionMoveLeft = false;
			}else if(event.keysym.scancode == SDL_SCANCODE_D){
				mActionMoveRight = false;
			}
		}
	}
}
