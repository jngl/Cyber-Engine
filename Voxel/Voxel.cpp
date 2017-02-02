#include "VoxelRenderer.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

#include <SDL.h>

int main(){
    SDL_Init(SDL_INIT_VIDEO); 
    SDL_Window* window = SDL_CreateWindow("Voxel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 200, 0);
	
    SDL_Surface* screen = SDL_GetWindowSurface(window);
	
	VoxelRenderer renderer(static_cast<uint32_t*>(screen->pixels), screen->w, screen->h);
	renderer.loadScene();
	
	bool cont = true;
	math::Vector3f camPos;
	
	const float speed = 0.25f;
	
	Timer timer;
	
	while(cont){
		SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                cont = false;
            }
        }
        
        float time = timer.timeInSecond();
        camPos = {25.f + 10 * math::cos(time*speed), 30, 25.f + 10.f * math::sin(time*speed)};
        
        renderer.getSceneRef().getCameraRef().set(camPos, math::Vector3f{25.f, 10.0f, 25.0f});
        
        SDL_LockSurface(screen);
		
		renderer.render();

		SDL_UnlockSurface(screen);
        
		SDL_UpdateWindowSurface(window);
        
	}
	
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


