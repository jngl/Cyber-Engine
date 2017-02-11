#pragma once

#include "Math/Matrix4.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector2.hpp"

#include "Renderer/Renderer.hpp"

class BoxelCamera
{
public:
  BoxelCamera();
  
  void update(float frameTime);
  
  void setActive();
  
private:
  Renderer::Camera_handle mRendererCamera;
  
  float dist;
  math::Vector2f angle;
};
