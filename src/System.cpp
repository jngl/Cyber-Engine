#include "System.hpp"

#include <GL/glew.h>

#include <string>

#include "Core/Error.hpp"
    
core::EventManager<System::Key> mKeydown;
core::EventManager<System::Key> mKeyup;
SDL_Window *mWindow;
SDL_GLContext mGLContext;
bool mOpen = true;

namespace System
{
    void init(int width, int height){    
        //init sdl
        if (SDL_Init(SDL_INIT_VIDEO) != 0){
            throw core::Error(std::string("SDL_Init Error: ")+ SDL_GetError());
        }
        
        //GL Attribute
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        //sdl window
        mWindow = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_OPENGL);

        if (mWindow == nullptr){
            throw core::Error(std::string("SDL_CreateWindow Error: ")+ SDL_GetError());
        }
        
        
        // opengl contex
        mGLContext = SDL_GL_CreateContext(mWindow);

        if (mGLContext == nullptr){
            throw core::Error(std::string("SDL_GL_CreateContext Error: ")+ SDL_GetError());
        }
        
        //glew
        GLenum err = glewInit();
        if (GLEW_OK != err){
            const char* erroMsg = (const char*)(glewGetErrorString(err));
            throw core::Error(std::string("GLEW Error: ")+ erroMsg);
        }
    }

    void destroy(){
        if(mGLContext!=nullptr){
            SDL_GL_DeleteContext(mGLContext);
        }
        if(mWindow!=nullptr){
            SDL_DestroyWindow(mWindow);
        }
        SDL_Quit();
    }

    bool isRunning(){
        return mOpen;
    }

    void clear(){
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    void endFrame(){
        SDL_GL_SwapWindow(mWindow);
    }

    void doEvent(){
        //Event Polling
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                mOpen = false;
            }else if (e.type == SDL_KEYDOWN){
                if(e.key.repeat==0){
                    mKeydown.send(static_cast<Key>(e.key.keysym.sym));
                }
            }else if(e.type == SDL_KEYUP){
                if(e.key.repeat==0){
                    mKeyup.send(static_cast<Key>(e.key.keysym.sym));
                }
            }
        }
    }
    void addKeydownListener(std::function<void(Key)> l){
        mKeydown.addListener(l);
    }

    void addKeyupListener(std::function<void(Key)> l){
        mKeyup.addListener(l);
    }
    
    bool keyIsPressed(Key k){
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        return state[SDL_GetScancodeFromKey((SDL_Keycode)k)];
    }

    void close(){
        mOpen=false;
    }
}
