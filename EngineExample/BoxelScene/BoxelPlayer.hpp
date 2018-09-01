#pragma once

#include <CyberEngine.hpp>

class BoxelPlayer
{
public:
  BoxelPlayer();

  void addAction(Window& window);

private:
  Renderer::Object mObject;
};