//g++ -std=c++11 tetris.cpp `sdl2-config --cflags --libs`

/* TODO
 * menu
 * next tetromino
 * retenir une pièce
 * pause
 * afficher score
 */


/**********************************************
 * Include
 *********************************************/
#define CYBER_ENGINE_IMPL
#include "CyberEngine.hpp"

#include <random>

using namespace std;

/**********************************************
 * Constante
 *********************************************/
const int BLOCK_SIZE = 32;

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 20;

/**********************************************
 * Tetrominos
 *********************************************/

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
  void draw(cy::Vector2i pPosition, int pSize, cy::Renderer& pRenderer) const;
  
  std::array<cy::Vector2i, 4> mBlock;
  cy::Color mColor;

  static cy::Texture& getTexture();
};

/**********************************************
 * Board
 *********************************************/
class Board
{
public:
  Board();
  void add(Tetromino pTetrominos, int pPositionX, int pPosistionY);
  bool empty(int pPositionX, int pPosistionY) const;
  void draw(cy::Renderer& pRenderer) const;
  
private:
  cy::Color mBlocks[BOARD_SIZE_X][BOARD_SIZE_Y];
  int mScore;
  cy::Texture mBackTexture;
};

/**********************************************
 * Player
 *********************************************/
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

/**********************************************
 * Game
 *********************************************/
class Game : public cy::Application
{
public:
  Game();
  
protected:  
  void frame(cy::Renderer& pRenderer) override;
  void onKey(cy::Key pKey, bool pPress) override;
  
private:
  Board mBoard;
  Player mPlayer;
  
  cy::Timer mHoryzontalMoveTimer;
  cy::Timer mVerticalMoveTimer;
  
  std::random_device mRNGSeed;
  std::default_random_engine mRNG;
  std::uniform_int_distribution<int> mRNGUniformTetromino;
  
  Tetromino::Enum mCurrentTetrominoEnum;  
  Tetromino       mCurrentTetrominoData;
  cy::Vector2i    mCurrentPosition;
  float mDefaultFallSpeed;
  float mFallSpeed;
  bool mQuickFall;
  
  bool mIsFinished;
  
  //private func
  void moveHoryzontal(int pValue);
  void moveVertical();
  void move(int pMoveX, int pMoveY);
  
  void rotate(bool trigo);
  
  void newTetromio();
};

/**********************************************
 * Tetrominos Implementation
 *********************************************/
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

void Tetromino::draw(cy::Vector2i pPosition, int pSize, cy::Renderer& pRenderer) const{
  cy::Texture& texture = Tetromino::getTexture();
  texture.use();
  pRenderer.setStrokeColor(0,255,0,0).setFillColor(mColor);
  for(int i(0); i<4; ++i){
    cy::Vector2i lPos = mBlock[i];
    pRenderer.rect(pPosition.x + lPos.x*pSize, pPosition.y + lPos.y*pSize, pSize, pSize);
  }
}

cy::Texture& Tetromino::getTexture(){
  static std::unique_ptr<cy::Texture> tex(new cy::Texture("block.png"));
  return *tex;
}

/**********************************************
 * Board Implementation
 *********************************************/
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
void Board::draw(cy::Renderer& pRenderer) const{
  mBackTexture.use();
  
  pRenderer.rect(0,0,320, 640, 10, 20);
  
  Tetromino::getTexture().use();
  for(int x(0); x<BOARD_SIZE_X; ++x){
    for(int y(0); y<BOARD_SIZE_Y; ++y){
      if(mBlocks[x][y].a!=0){
        pRenderer.setStrokeColor(0,0,0,0).setFillColor(mBlocks[x][y]).rect(x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      }
    }
  }
}

/**********************************************
 * Player Implementation
 *********************************************/
Player::Player():
mHoryzontalMoveActionLeft(false),
mHoryzontalMoveActionRight(false)
{
}

Player::~Player(){
}
  
bool Player::isHoryzontalMoveActionLeft(){
  return mHoryzontalMoveActionLeft;
}

bool Player::isHoryzontalMoveActionRight(){
  return mHoryzontalMoveActionRight;
}

void Player::setHoryzontalMoveActionLeft(bool v){
  mHoryzontalMoveActionLeft = v;
}

void Player::setHoryzontalMoveActionRight(bool v){
  mHoryzontalMoveActionRight = v;
}


/**********************************************
 * Game Implementation
 *********************************************/
Game::Game():
cy::Application(1024, 768),
mRNG(mRNGSeed()),
mRNGUniformTetromino(0, Tetromino::Enum_Size-1),
mCurrentTetrominoEnum(static_cast<Tetromino::Enum>(mRNGUniformTetromino(mRNG))),
mCurrentTetrominoData(Tetromino::get(mCurrentTetrominoEnum)),
mCurrentPosition(4, 0),
mDefaultFallSpeed(0.5),
mFallSpeed(mDefaultFallSpeed),
mQuickFall(false),
mIsFinished(false)
{
}

void Game::frame(cy::Renderer& pRenderer){
  if(!mIsFinished){
    //update
    if(mPlayer.isHoryzontalMoveActionLeft() && !mPlayer.isHoryzontalMoveActionRight()){
      moveHoryzontal(-1);
    }else if(!mPlayer.isHoryzontalMoveActionLeft() && mPlayer.isHoryzontalMoveActionRight()){
      moveHoryzontal(1);
    }
    moveVertical();
  }
  
  //render
  pRenderer.setFillColor(255).clear();
  
  mBoard.draw(pRenderer);
  
  if(!mIsFinished)mCurrentTetrominoData.draw({mCurrentPosition.x*BLOCK_SIZE, mCurrentPosition.y*BLOCK_SIZE}, BLOCK_SIZE, pRenderer);
}

void Game::onKey(cy::Key pKey, bool pPress){
  if(!mIsFinished){
    switch(pKey){
      case cy::Key_LEFT:
        mPlayer.setHoryzontalMoveActionLeft(!mPlayer.isHoryzontalMoveActionLeft());
        break;
      case cy::Key_RIGHT:
        mPlayer.setHoryzontalMoveActionRight(!mPlayer.isHoryzontalMoveActionRight());
        break;
      case cy::Key_SPACE:
        if(pPress)mFallSpeed=0.0f;
        break;
      case cy::Key_s:
        mQuickFall = !mQuickFall;
        break;
      case cy::Key_q:
        if(pPress)rotate(true);
        break;
      case cy::Key_d:
        if(pPress)rotate(false);
        break;
      default:
        break;
    }
  }
}

void Game::moveHoryzontal(int pValue){
  if(mHoryzontalMoveTimer.timeInSecond()<0.1f){
    return;
  }
  mHoryzontalMoveTimer.restart();
  
  move(pValue, 0);
}

void Game::moveVertical(){
  float speed = mFallSpeed;
  if(mQuickFall)speed/=8;
  if(mVerticalMoveTimer.timeInSecond()<speed){
    return;
  }
  mVerticalMoveTimer.restart();
  
  move(0, 1);
}

void Game::move(int pMoveX, int pMoveY){
  mCurrentPosition.x+=pMoveX;
  mCurrentPosition.y+=pMoveY;
  
  bool ok = true;
  bool cont;
  for(int i(0); i<4; ++i){
    cy::Vector2i pos = mCurrentTetrominoData.mBlock[i];
    pos.x+=mCurrentPosition.x;
    pos.y+=mCurrentPosition.y;
    
    if(pos.x<0 || pos.x>=BOARD_SIZE_X){
      ok=false;
      cont=true;
    }else if(pos.y<0 || pos.y>=BOARD_SIZE_Y){
      ok=false;
      cont=false;
    }else if(!mBoard.empty(pos.x,pos.y)){
      if(pMoveY==0){
        ok=false;
        cont=true;
      }else{
        ok=false;
        cont=false;
      }
    }
  }
  
  if(!ok){
    mCurrentPosition.x-=pMoveX;
    mCurrentPosition.y-=pMoveY;
    
    if(!cont){
      mBoard.add(mCurrentTetrominoData, mCurrentPosition.x, mCurrentPosition.y);
      newTetromio();
    }
  }
}

void Game::rotate(bool trigo){
  mCurrentTetrominoData.rotate(mCurrentTetrominoEnum, trigo);
  
  bool ok = true;
  for(int i(0); i<4; ++i){
    cy::Vector2i pos = mCurrentTetrominoData.mBlock[i];
    pos.x+=mCurrentPosition.x;
    pos.y+=mCurrentPosition.y;
    
    if(pos.x<0 || pos.x>=BOARD_SIZE_X || pos.y<0 || pos.y>=BOARD_SIZE_Y || !mBoard.empty(pos.x,pos.y)){
      ok=false;
    }
  }
  
  if(!ok){
    mCurrentTetrominoData.rotate(mCurrentTetrominoEnum, !trigo);
  }
}

void Game::newTetromio(){
  mCurrentPosition.y=0;
  mCurrentPosition.x=4;
  mCurrentTetrominoEnum = static_cast<Tetromino::Enum>(mRNGUniformTetromino(mRNG));
  mCurrentTetrominoData = Tetromino::get(mCurrentTetrominoEnum);
  mDefaultFallSpeed*=0.99f;
  mFallSpeed=mDefaultFallSpeed;
  
  for(int i(0); i<4; ++i){
    cy::Vector2i pos = mCurrentTetrominoData.mBlock[i];
    pos.x+=mCurrentPosition.x;
    pos.y+=mCurrentPosition.y;
    
    if(!mBoard.empty(pos.x,pos.y)){
      mIsFinished = true;
    }
  }
}

/**********************************************
 * Main
 *********************************************/
int main(){
  try{
  Game lGame;
  lGame.run();
  return 0;
  }catch(cy::Error& e){
    std:cerr<<e.getMessage()<<std::endl;
  }
}

