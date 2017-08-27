#pragma once

#include "CyberEngine.hpp"

class Player
{
public:
  Player();
  ~Player();
  
  bool isHoryzontalMoveActionLeft();
  bool isHoryzontalMoveActionRight();
  void setHoryzontalMoveActionLeft(bool v);
  void setHoryzontalMoveActionRight(bool v);
  
private:
  bool mHoryzontalMoveActionLeft;
  bool mHoryzontalMoveActionRight;
};
