#include <glad/glad.h>

#include "System.hpp"

#include <string>
#include <iostream>

#include "Core/Error.hpp"

#include "Renderer/GLDebug.hpp"
    
core::EventManager<System::Key> mKeydown;
core::EventManager<System::Key> mKeyup;
SDL_Window *mWindow = nullptr;
SDL_GLContext mGLContext = nullptr;
bool mOpen = true;

#ifdef GLAD_DEBUG
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
    printf("Calling: %s (%d arguments)\n", name, len_args);
}
#endif

namespace System
{
    void init(int width, int height){    
        //init sdl
        if (SDL_Init(SDL_INIT_VIDEO) != 0){
            throw core::Error(std::string("SDL_Init Error: ")+ SDL_GetError());
        }
        
        
        // OpenGL 3.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        
        // Double Buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        //sdl window
        mWindow = SDL_CreateWindow("Cyber engine", 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (mWindow == nullptr){
            throw core::Error(std::string("SDL_CreateWindow Error: ")+ SDL_GetError());
        }
        
        
        // opengl contex
        mGLContext = SDL_GL_CreateContext(mWindow);

        if (mGLContext == nullptr){
            throw core::Error(std::string("SDL_GL_CreateContext Error: ")+ SDL_GetError());
        }
        
        SDL_GL_MakeCurrent(mWindow, mGLContext);
        
        //glad
        if(!gladLoadGL()) {
            throw core::Error("Something went wrong with glad");
        }

#ifdef GLAD_DEBUG
        // before every opengl call call pre_gl_call
       // glad_set_pre_callback(pre_gl_call);
        // don't use the callback for glClear
        // (glClear could be replaced with your own function)
        glad_debug_glClear = glad_glClear;
#endif

        std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<", GLSL "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
        
        glCheckError(__FILE__, __LINE__);


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
