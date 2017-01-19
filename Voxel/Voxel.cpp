#include "VoxelRenderer.hpp"

int main(){
    
    VoxelRenderer renderer;
    renderer.loadScene();
    renderer.render();
    renderer.save();
}


