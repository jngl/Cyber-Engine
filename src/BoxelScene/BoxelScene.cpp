#include "BoxelScene.hpp"

BoxelScene::BoxelScene(){
  chunk.loadTexture();
  chunk.generateGrid();
  chunk.generateMesh();
}
  
void BoxelScene::update(float frameTime){
  mCamera.update(frameTime);
}
  
void BoxelScene::draw(){
  mCamera.setActive();
  chunk.draw();
}
