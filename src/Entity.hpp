#pragma once

#include "Renderer/Mesh.hpp"
#include "Math/Vector3.hpp"
#include "Math/Angle3.hpp"

class Entity
{
public:
  Entity();
  
  void draw();
  
    Mesh* mesh;
    math::Vec3f position;
    math::Angle3f rotation;
};
