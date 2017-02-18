#include "VoxelWindow.hpp"

VoxelWindow::VoxelWindow()
{
	SDL_Init(SDL_INIT_VIDEO); 
    window = SDL_CreateWindow("Voxel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 200, 0);
	screen = SDL_GetWindowSurface(window);
}

VoxelWindow::~VoxelWindow()
{
	SDL_DestroyWindow(window);
    SDL_Quit();
}

void VoxelWindow::updateSurface(){
	SDL_UpdateWindowSurface(window);
}

uint32_t* VoxelWindow::getPixels(){
	return static_cast<uint32_t*>(screen->pixels);
}

int VoxelWindow::getWidth(){
	return screen->w;
}

int VoxelWindow::getHeight(){
	return screen->h;
}
	
void VoxelWindow::lock(){
	SDL_LockSurface(screen);
}

void VoxelWindow::unlock(){
	SDL_UnlockSurface(screen);
}
