#pragma once

/**********************************************
 * Include
 *********************************************/
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <iostream>
#include <memory>
#include <chrono>

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
    void rect(int x, int y, int w, int h, float u = 1, float v= 1) ;
    
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
  * Key
  *********************************************/

  typedef int Key;
  enum Key_Enum
  {
      Key_UNKNOWN = 0,

      Key_RETURN = '\r',
      Key_ESCAPE = '\033',
      Key_BACKSPACE = '\b',
      Key_TAB = '\t',
      Key_SPACE = ' ',
      Key_EXCLAIM = '!',
      Key_QUOTEDBL = '"',
      Key_HASH = '#',
      Key_PERCENT = '%',
      Key_DOLLAR = '$',
      Key_AMPERSAND = '&',
      Key_QUOTE = '\'',
      Key_LEFTPAREN = '(',
      Key_RIGHTPAREN = ')',
      Key_ASTERISK = '*',
      Key_PLUS = '+',
      Key_COMMA = ',',
      Key_MINUS = '-',
      Key_PERIOD = '.',
      Key_SLASH = '/',
      Key_0 = '0',
      Key_1 = '1',
      Key_2 = '2',
      Key_3 = '3',
      Key_4 = '4',
      Key_5 = '5',
      Key_6 = '6',
      Key_7 = '7',
      Key_8 = '8',
      Key_9 = '9',
      Key_COLON = ':',
      Key_SEMICOLON = ';',
      Key_LESS = '<',
      Key_EQUALS = '=',
      Key_GREATER = '>',
      Key_QUESTION = '?',
      Key_AT = '@',
      /*
        Skip uppercase letters
      */
      Key_LEFTBRACKET = '[',
      Key_BACKSLASH = '\\',
      Key_RIGHTBRACKET = ']',
      Key_CARET = '^',
      Key_UNDERSCORE = '_',
      Key_BACKQUOTE = '`',
      Key_a = 'a',
      Key_b = 'b',
      Key_c = 'c',
      Key_d = 'd',
      Key_e = 'e',
      Key_f = 'f',
      Key_g = 'g',
      Key_h = 'h',
      Key_i = 'i',
      Key_j = 'j',
      Key_k = 'k',
      Key_l = 'l',
      Key_m = 'm',
      Key_n = 'n',
      Key_o = 'o',
      Key_p = 'p',
      Key_q = 'q',
      Key_r = 'r',
      Key_s = 's',
      Key_t = 't',
      Key_u = 'u',
      Key_v = 'v',
      Key_w = 'w',
      Key_x = 'x',
      Key_y = 'y',
      Key_z = 'z',

      Key_CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

      Key_F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
      Key_F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
      Key_F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
      Key_F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
      Key_F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
      Key_F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
      Key_F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
      Key_F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
      Key_F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
      Key_F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
      Key_F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
      Key_F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

      Key_PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
      Key_SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
      Key_PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
      Key_INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
      Key_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
      Key_PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
      Key_DELETE = '\177',
      Key_END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
      Key_PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
      Key_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
      Key_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
      Key_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
      Key_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

      Key_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
      Key_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
      Key_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
      Key_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
      Key_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
      Key_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
      Key_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
      Key_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
      Key_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
      Key_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
      Key_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
      Key_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
      Key_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
      Key_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
      Key_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
      Key_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
      Key_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

      Key_APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
      Key_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
      Key_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
      Key_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
      Key_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
      Key_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
      Key_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
      Key_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
      Key_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
      Key_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
      Key_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
      Key_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
      Key_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
      Key_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
      Key_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
      Key_EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
      Key_HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
      Key_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
      Key_SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
      Key_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
      Key_AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
      Key_UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
      Key_CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
      Key_COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
      Key_PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
      Key_FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
      Key_MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
      Key_VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
      Key_VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
      Key_KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
      Key_KP_EQUALSAS400 =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

      Key_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
      Key_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
      Key_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
      Key_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
      Key_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
      Key_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
      Key_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
      Key_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
      Key_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
      Key_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
      Key_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
      Key_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

      Key_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
      Key_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
      Key_THOUSANDSSEPARATOR =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
      Key_DECIMALSEPARATOR =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
      Key_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
      Key_CURRENCYSUBUNIT =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
      Key_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
      Key_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
      Key_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
      Key_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
      Key_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
      Key_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
      Key_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
      Key_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
      Key_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
      Key_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
      Key_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
      Key_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
      Key_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
      Key_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
      Key_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
      Key_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
      Key_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
      Key_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
      Key_KP_DBLAMPERSAND =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
      Key_KP_VERTICALBAR =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
      Key_KP_DBLVERTICALBAR =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
      Key_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
      Key_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
      Key_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
      Key_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
      Key_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
      Key_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
      Key_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
      Key_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
      Key_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
      Key_KP_MEMSUBTRACT =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
      Key_KP_MEMMULTIPLY =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
      Key_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
      Key_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
      Key_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
      Key_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
      Key_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
      Key_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
      Key_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
      Key_KP_HEXADECIMAL =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

      Key_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
      Key_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
      Key_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
      Key_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
      Key_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
      Key_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
      Key_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
      Key_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

      Key_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

      Key_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
      Key_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
      Key_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
      Key_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
      Key_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
      Key_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
      Key_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
      Key_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
      Key_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
      Key_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
      Key_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
      Key_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
      Key_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
      Key_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
      Key_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
      Key_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
      Key_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

      Key_BRIGHTNESSDOWN =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
      Key_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
      Key_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
      Key_KBDILLUMTOGGLE =
          SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
      Key_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
      Key_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
      Key_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
      Key_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
      Key_APP1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
      Key_APP2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),
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
    virtual void frame(Renderer& pRenderer) = 0;
    virtual void onKey(Key pKey, bool pPress) = 0;
    
    void close();
    bool isOpen();
    
  private:
    SDL_Window* mWindow;
    std::unique_ptr<Renderer> mRenderer;
    bool mOpen;
  };
}
