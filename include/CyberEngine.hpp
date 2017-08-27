#pragma once

/**********************************************
 * Include
 *********************************************/
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <iostream>
#include <memory>
#include <chrono>

#include "Key.hpp"

/**********************************************
 * Start
 *********************************************/
namespace cy
{
  /**********************************************
  * Error
  *********************************************/
  class Error 
  {
  public:
    Error(std::string pMessage);
    std::string getMessage();
    
  private:
    std::string mMessage;
  };

  void mustBeTrue(bool pCondition, std::string pMessage);

  #ifdef DEBUG
  #define ASSERT(pCondition, pMessage) mustBeTrue(pCondition, pMessage)
  #else
  #define ASSERT(pCondition, pMessage)
  #endif

  /**********************************************
  * Color
  *********************************************/
  struct Color
  {
    Uint8 r, g, b, a;
  };
  
  /**********************************************
  * Math
  *********************************************/
  template<class T>
  struct Vector2{
    union{
      struct{
        T x, y;
      };
      struct{
        T width, height;
      };
      struct{
        T array[2];
      };
    };
    
    constexpr Vector2():
    x(0),
    y(0){
    }
    
    constexpr Vector2(T pX, T pY):
    x(pX),
    y(pY){
    }
  };
  
  typedef Vector2<float> Vector2f;
  typedef Vector2<int> Vector2i;
  
  /**********************************************
  * Timer
  *********************************************/
  class Timer
  {
  public:
      Timer();
      
      float timeInSecond();
      
      void restart();
      
  private:
      typedef std::chrono::high_resolution_clock::time_point TimePoint;
      typedef std::chrono::duration<float> Duration;
      
      TimePoint mTimeStart;
      
      TimePoint now();
  };
  
  /**********************************************
  * Texture
  *********************************************/
  
  class Texture{
  public:
    Texture(std::string filename);
    ~Texture();
    
    void use() const;
    
    int getHeight();
    int getWidth();
    
    std::string getName();

		private:
			unsigned int mId;
			int mWidth, mHeight;
			std::string mName;
	};

  /**********************************************
  * Renderer
  *********************************************/
  
  class Renderer
  {
  public:
    friend class Application;
    
    Renderer(SDL_Window* pWindow);
    ~Renderer();
    
    void clear();
    void rect(float x, float y, float w, float h, float u = 1, float v= 1) ;
    
    Renderer& setFillColor(Uint8 pGrey);
    Renderer& setFillColor(Uint8 r, Uint8 g, Uint8 b);
    Renderer& setFillColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Renderer& setFillColor(Color pColor);
    
    Renderer& setStrokeColor(Uint8 pGrey);
    Renderer& setStrokeColor(Uint8 r, Uint8 g, Uint8 b);
    Renderer& setStrokeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Renderer& setStrokeColor(Color pColor);
    
  protected:
    SDL_GLContext mGlContext;
    Color mFillColor;
    Color mStrokeColor;
  };

  /**********************************************
  * Application
  *********************************************/
  class Application
  {
  public:
    Application(int width, int height);
    virtual ~Application();
    
    void run();
    
  protected:  
    virtual void frame(Renderer& pRenderer, int width, int height) = 0;
    virtual void onKey(Key pKey, bool pPress) = 0;
    
    void close();
    bool isOpen();
    
  private:
    SDL_Window* mWindow;
    std::unique_ptr<Renderer> mRenderer;
    bool mOpen;
  };
}
