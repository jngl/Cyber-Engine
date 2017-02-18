#include "VoxelRenderer.hpp"
#include "VoxelWindow.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

#include <iostream>

int main(){
	VoxelWindow window;
	
	VoxelRenderer renderer(window.getWidth(), window.getHeight());
	renderer.loadScene();
	
	bool cont = true;
	math::Vector3f camPos;
	
	const float speed = 0.25f;
	
	Timer timer;
	float time;
	
	while(cont){
		SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                cont = false;
            }
        }
        
        float frameTime =  timer.timeInSecond();
		timer.restart();
        time += frameTime;
        camPos = {25.f + 10 * math::cos(time*speed), 30, 25.f + 10.f * math::sin(time*speed)};
		
		std::cout<<"\rFPS : "<< 1.f/frameTime<<std::flush;
        
        renderer.getSceneRef().getCameraRef().set(camPos, math::Vector3f{25.f, 10.0f, 25.0f});
        
        window.lock();
		
		renderer.render(window.getPixels());

		window.unlock();
        
		window.updateSurface();
        
	}
    return 0;
}


