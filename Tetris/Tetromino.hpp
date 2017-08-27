#pragma once

#include "CyberEngine.hpp"

class Tetromino
{
public:
  enum Enum
  {
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z,
    Enum_Size
  };

  constexpr Tetromino(cy::Vector2i pBlock1, cy::Vector2i pBlock2, cy::Vector2i pBlock3, cy::Vector2i pBlock4, cy::Color pColor);
  constexpr Tetromino(const Tetromino& pTest);

  static const Tetromino& get(Enum pEnum);
  
  void rotate(Enum type, bool trigo);
  void draw(cy::Vector2f pPosition, float pSize, cy::Renderer& pRenderer) const;

  static cy::Texture& getTexture();
  
  std::array<cy::Vector2i, 4> mBlock;
  cy::Color mColor;
};


constexpr Tetromino::Tetromino(cy::Vector2i pBlock1, cy::Vector2i pBlock2, cy::Vector2i pBlock3, cy::Vector2i pBlock4, cy::Color pColor):
mBlock({pBlock1, pBlock2, pBlock3, pBlock4}),
mColor(pColor)
{

}

constexpr Tetromino::Tetromino(const Tetromino& pTest):
mBlock(pTest.mBlock),
mColor(pTest.mColor)
{

}
