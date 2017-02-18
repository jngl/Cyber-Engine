#include "VoxelRenderer.hpp"
#include "VoxelWindow.hpp"

#include "PlatformIndependenceLayer/Timer.hpp"

int main(){
	VoxelWindow window;
	
	VoxelRenderer renderer(window.getPixels(), window.getWidth(), window.getHeight());
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
        
        window.lock();
		
		renderer.render();

		window.unlock();
        
		window.updateSurface();
        
	}
    return 0;
}


