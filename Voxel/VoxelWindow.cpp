#include "VoxelWindow.hpp"

VoxelWindow::VoxelWindow()
{
	SDL_Init(SDL_INIT_VIDEO); 
    window = SDL_CreateWindow("Voxel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getWidth(), getHeight(), 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	texture = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_STREAMING,
                            getWidth(), getHeight());
	
	surface = SDL_CreateRGBSurfaceFrom(NULL,
                                   getWidth(), getHeight(),
                                   32, 0,
                                   0x00FF0000,
                                   0x0000FF00,
                                   0x000000FF,
                                   0xFF000000);
}

VoxelWindow::~VoxelWindow()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

void VoxelWindow::updateSurface(){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

uint32_t* VoxelWindow::getPixels(){
	return static_cast<uint32_t*>(surface->pixels);
}

int VoxelWindow::getWidth(){
	return 450;
}

int VoxelWindow::getHeight(){
	return 300;
}
	
void VoxelWindow::lock(){
	SDL_LockTexture(texture, NULL,
                &surface->pixels,
                &surface->pitch);
}

void VoxelWindow::unlock(){
	SDL_UnlockTexture(texture);
}
