#include "CyberEngine.hpp"

#include "stb_image.h"

namespace cy
{
  
  /**********************************************
  * Error Implementation
  *********************************************/
  Error::Error(std::string pMessage):
  mMessage(pMessage)
  {
  }

  std::string Error::getMessage(){
    return mMessage;
  }

  void mustBeTrue(bool pCondition, std::string pMessage){
    if(!pCondition){
      throw Error(pMessage);
    }
  }
  
  /**********************************************
  * Timer Implementation
  *********************************************/
  Timer::Timer():
  mTimeStart(now())
  {
  }

  float Timer::timeInSecond(){
      TimePoint t2 = now();
      Duration time_span = std::chrono::duration_cast<Duration>(t2 - mTimeStart);
      return time_span.count();
  }

  void Timer::restart(){
      mTimeStart = now();
  }

  Timer::TimePoint Timer::now(){
      return std::chrono::high_resolution_clock::now();
  }

  /**********************************************
  * Application Implementation
  *********************************************/
  Application::Application(int width, int height):
  mWindow(nullptr),
  mOpen(true)
  {
    mustBeTrue(SDL_Init(SDL_INIT_VIDEO)==0, std::string("SDL could not initialize! SDL_Error: ")+SDL_GetError());

    //window
    mWindow = SDL_CreateWindow( "BattleGame",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    mustBeTrue(mWindow != nullptr, std::string("Window could not be created! SDL_Error: ")+SDL_GetError());

    mRenderer.reset(new Renderer(mWindow));
  }

  Application::~Application(){
    mRenderer.reset(); 
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  void Application::run(){
    while(isOpen()){
      
      SDL_Event lEvent;
      while (SDL_PollEvent(&lEvent)) {
        switch(lEvent.type){
          case SDL_QUIT:
            close();
            break;
          case SDL_KEYDOWN:
            if(lEvent.key.repeat==0){
              onKey(lEvent.key.keysym.sym, true);
            }
            break;
          case SDL_KEYUP:
            if(lEvent.key.repeat==0){
              onKey(lEvent.key.keysym.sym, false);
            }
            break;
          default:
            break;
        }
      }
      
      int width, height;
      SDL_GetWindowSize(mWindow, &width, &height);
      
      glViewport( 0, 0, width, height );
    
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity( );
      glOrtho(0, width, height, 0, -100, 100);
      
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity( );

      
      frame(*mRenderer);
      
      SDL_GL_SwapWindow(mWindow);
    }
  }

  void Application::close(){
    mOpen = false;
  }

  bool Application::isOpen(){
    return mOpen;
  }
  
  /**********************************************
  * Texture Implementation
  *********************************************/
  
  Texture::Texture(std::string filename):
  mId(0),
	mWidth(0),
	mHeight(0),
	mName(filename)
	{
		int channels;
		unsigned char* ptr = stbi_load(filename.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

		if( ptr==NULL || mWidth==0 || mHeight==0){
			throw Error(std::string("no texture file \"")+filename+"\"");
		}

		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		unsigned char* pixels=&(ptr[mWidth * (mHeight-1) * 4]);
		for(int y(0);y<mHeight;y++){
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, y, mWidth, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			pixels-=mWidth*4;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(ptr);
  }
  Texture::~Texture(){
    glDeleteTextures(1, &mId);
  }
  void Texture::use() const{
    glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, mId);
  }
  int Texture::getHeight(){
    return mHeight;
  }
  int Texture::getWidth(){
    return mWidth;
  }
  std::string Texture::getName(){
    return mName;    
  }

  /**********************************************
  * Renderer Implementation
  *********************************************/
  Renderer::Renderer(SDL_Window* pWindow):
  mFillColor({255,0,0,255}),
  mStrokeColor({255,255,255,255})
  {
    mGlContext = SDL_GL_CreateContext(pWindow);
    mustBeTrue(mGlContext != nullptr, std::string("Renderer could not be created! SDL_Error: ")+SDL_GetError());
    
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  Renderer::~Renderer(){
    SDL_GL_DeleteContext(mGlContext);  
  }

  Renderer& Renderer::setFillColor(Uint8 pGrey){
    mFillColor.r = mFillColor.g = mFillColor.b = pGrey;
    return *this;
  }
  Renderer& Renderer::setFillColor(Uint8 r, Uint8 g, Uint8 b){
    mFillColor.r = r;
    mFillColor.g = g;
    mFillColor.b = b;
    return *this;
  }
  Renderer& Renderer::setFillColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    mFillColor.r = r;
    mFillColor.g = g;
    mFillColor.b = b;
    mFillColor.a = a;
    return *this;
  }
  
  Renderer& Renderer::setFillColor(Color pColor){
    mFillColor = pColor;
    return *this;
  }

  Renderer& Renderer::setStrokeColor(Uint8 pGrey){
    mStrokeColor.r = mStrokeColor.g = mStrokeColor.b = pGrey;
    return *this;
  }
  Renderer& Renderer::setStrokeColor(Uint8 r, Uint8 g, Uint8 b){
    mStrokeColor.r = r;
    mStrokeColor.g = g;
    mStrokeColor.b = b;
    return *this;
  }
  Renderer& Renderer::setStrokeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    mStrokeColor.r = r;
    mStrokeColor.g = g;
    mStrokeColor.b = b;
    mStrokeColor.a = a;
    return *this;
  }
  
  Renderer& Renderer::setStrokeColor(Color pColor){
    mStrokeColor = pColor;
    return *this;
  }

  void Renderer::clear(){
    glClearColor(mFillColor.r,mFillColor.g,mFillColor.b,mFillColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  
  void Renderer::rect(int x, int y, int w, int h, float u, float v){
    //fill
    glBegin(GL_QUADS);
    glColor4ub(mFillColor.r, mFillColor.g, mFillColor.b, mFillColor.a);
    
    glTexCoord2f(0, v);
    glVertex2i(x, y);
    glTexCoord2f(0, 0);
    glVertex2i(x, y+h);
    glTexCoord2f(u, 0);
    glVertex2i(x+w, y+h);
    glTexCoord2f(u, v);
    glVertex2i(x+w, y);
    glEnd();
      
    //stroke
    glColor4ub(mStrokeColor.r, mStrokeColor.g, mStrokeColor.b, mStrokeColor.a);
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x, y+h);
    glVertex2i(x+w, y+h);
    glVertex2i(x+w, y);
    glEnd();
    
    mustBeTrue(glGetError()==GL_NO_ERROR, "Renderer::Rect : opengl error");
  }
}
