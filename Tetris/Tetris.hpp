#pragma once

#include "CyberEngine.hpp"

#include "Tetromino.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <random>

using namespace std;

/**********************************************
 * Game
 *********************************************/
class Game : public cy::Application
{
public:
  Game();
  
protected:  
  void frame(cy::Renderer& pRenderer, int width, int height) override;
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

