#pragma once

#include <SDL.h>

class VoxelWindow
{
public:
	VoxelWindow();
	~VoxelWindow();
	
	void updateSurface();
	
	uint32_t* getPixels();
	
	int getWidth();
	int getHeight();
	
	void lock();
	void unlock();
	
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};
