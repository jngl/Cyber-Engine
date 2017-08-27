#include "Tetromino.hpp"



constexpr Tetromino gTetrominos[Tetromino::Enum_Size] = {
  { {-1, 0}, { 0, 0}, {1, 0}, {2, 0}, {  0, 255, 255, 255} }, //Tetromino::I
  { {-1, 0}, { 0, 0}, {1, 0}, {1, 1}, {  0,   0, 255, 255} }, //Tetromino::J
  { {-1, 1}, {-1, 0}, {0, 0}, {1, 0}, {255, 128,   0, 255} }, //Tetromino::L
  { { 0, 1}, { 0, 0}, {1, 0}, {1, 1}, {255, 255,   0, 255} }, //Tetromino::O
  { {-1, 1}, { 0, 1}, {0, 0}, {1, 0}, {  0, 255,   0, 255} }, //Tetromino::S
  { {-1, 0}, { 0, 0}, {0, 1}, {1, 0}, {128,   0, 128, 255} }, //Tetromino::T
  { {-1, 0}, { 0, 0}, {0, 1}, {1, 1}, {255,   0,   0, 255} }  //Tetromino::Z
};

const Tetromino& Tetromino::get(Enum pEnum){
  
  return gTetrominos[static_cast<int>(pEnum)];
}

void Tetromino::rotate(Tetromino::Enum type, bool trigo){
    if(type==Tetromino::O){
      return;
    }
    for(int i(0); i<4; ++i){
      cy::Vector2i pos = mBlock[i];
      
      std::swap(pos.x, pos.y);
      if(trigo) pos.y = -pos.y;
      else      pos.x = -pos.x;
      
      mBlock[i] = pos;
    }
}

void Tetromino::draw(cy::Vector2f pPosition, float pSize, cy::Renderer& pRenderer) const{
  cy::Texture& texture = Tetromino::getTexture();
  texture.use();
  pRenderer.setStrokeColor(0,255,0,0).setFillColor(mColor);
  for(int i(0); i<4; ++i){
    cy::Vector2i lPos = mBlock[i];
    pRenderer.rect(pPosition.x + pSize*lPos.x, pPosition.y + pSize*lPos.y, pSize, pSize);
  }
}

cy::Texture& Tetromino::getTexture(){
  static std::unique_ptr<cy::Texture> tex(new cy::Texture("block.png"));
  return *tex;
}
