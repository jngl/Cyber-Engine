#pragma once

#include <CyberBase.hpp>
#include <CyberEngine.hpp>

class BoxelCamera
{
public:
  BoxelCamera();
  
  void addAction(Window& window);
  
  void update(float frameTime);
  
private:
  Renderer::Camera_handle mRendererCamera;

  float mDist;
  cb::Vector3f mPosition;
  cb::Vector2f mAngle;
  
  bool mActionRotateUp, mActionRotateDown, mActionRotateLeft, mActionRotateRight, mActionMoveForward, mActionMoveBackward;
};