#pragma once

#include "CyberEngine.hpp"

#include "Tetromino.hpp"

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 20;

class Board
{
public:
  Board();
  void add(Tetromino pTetrominos, int pPositionX, int pPosistionY);
  bool empty(int pPositionX, int pPosistionY) const;
  void draw(cy::Renderer& pRenderer, float pBlockSize) const;
  
private:
  cy::Color mBlocks[BOARD_SIZE_X][BOARD_SIZE_Y];
  int mScore;
  cy::Texture mBackTexture;
};
