#pragma once

#include "BoxelCamera.hpp"

#include "BoxelChunk.hpp"

class BoxelScene
{
public:
  BoxelScene();
  
  void update(float frameTime);
  
  void draw();
  
private:
  BoxelCamera mCamera;
  BoxelChunk<10, 10, 10> chunk;
};
