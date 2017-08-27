#include "Board.hpp"

Board::Board():
mScore(0),
mBackTexture("back.png")
{
  for(int x(0); x<BOARD_SIZE_X; ++x){
    for(int y(0); y<BOARD_SIZE_Y; ++y){
      mBlocks[x][y].a=0;
    }
  }
}
void Board::add(Tetromino pTetrominos, int pPositionX, int pPosistionY){
  for(int i(0); i<4; ++i){
    cy::Vector2i pos = pTetrominos.mBlock[i];
    pos.x+=pPositionX;
    pos.y+=pPosistionY;
  
    mBlocks[pos.x][pos.y] = pTetrominos.mColor;
  }
  
  int point = 0;
  
  //remove all full row
  for(int y(0); y<BOARD_SIZE_Y; ++y){
    //test row
    bool isFull=true;
    for(int x(0); x<BOARD_SIZE_X; ++x){
      if(empty(x, y)){
        isFull=false;
      }
    }
    
    //remove and fall
    if(isFull){
      point=(point+1)*2;
      for(int x(0); x<BOARD_SIZE_X; ++x){
        for(int y2(y); y2>0; --y2){
          mBlocks[x][y2] = mBlocks[x][y2-1];
        }
      }
    }
  }
  
  mScore += point;
  if(point!=0){
    std::cout<<"score : "<<mScore<<std::endl;
  }
}
bool Board::empty(int pPositionX, int pPosistionY) const{
  return mBlocks[pPositionX][pPosistionY].a==0;
}
void Board::draw(cy::Renderer& pRenderer, float pBlockSize) const{
  mBackTexture.use();
  
  pRenderer.rect(0,0,pBlockSize*BOARD_SIZE_X, pBlockSize*BOARD_SIZE_Y, 10, 20);
  
  Tetromino::getTexture().use();
  for(int x(0); x<BOARD_SIZE_X; ++x){
    for(int y(0); y<BOARD_SIZE_Y; ++y){
      if(mBlocks[x][y].a!=0){
        pRenderer.setStrokeColor(0,0,0,0).setFillColor(mBlocks[x][y]).rect(x*pBlockSize, y*pBlockSize, pBlockSize, pBlockSize);
      }
    }
  }
}

