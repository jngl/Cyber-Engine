/* TODO
 * menu
 * next tetromino
 * retenir une pièce
 * pause
 * afficher score
 */
#include "Tetris.hpp"

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

void Game::frame(cy::Renderer& pRenderer, int width, int height){
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
  
  const float blockSize = static_cast<float>(height)/BOARD_SIZE_Y;
  
  mBoard.draw(pRenderer, blockSize);
  
  if(!mIsFinished)mCurrentTetrominoData.draw({mCurrentPosition.x*blockSize, mCurrentPosition.y*blockSize}, blockSize, pRenderer);
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

