#include "Draw.hpp"

#include <GL/gl.h>
#include <SDL.h>

#include "Engine.hpp"

Draw::Draw::Draw(Engine* engine)
{
	mEngine = engine;
}

void Draw::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Draw::ortho(float left, float right, float bottom, float top, float near_val, float far_val)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near_val, far_val);
}

void Draw::rect(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.f, 1.f);
	glVertex2f(x, y);
	
	glTexCoord2f(0.f, 1.f);
	glVertex2f(x+w, y);
	
	glTexCoord2f(0.f, 0.f);
	glVertex2f(x+w, y+h);
	
	glTexCoord2f(1.f, 0.f);
	glVertex2f(x, y+h);
	
	glEnd(); 
}

void Draw::rect(Rectf r)
{
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.f, 1.f);
	glVertex2f(r.x, r.y);
	
	glTexCoord2f(0.f, 1.f);
	glVertex2f(r.x+r.w, r.y);
	
	glTexCoord2f(0.f, 0.f);
	glVertex2f(r.x+r.w, r.y+r.h);
	
	glTexCoord2f(1.f, 0.f);
	glVertex2f(r.x, r.y+r.h);
	
	glEnd(); 
}

void Draw::setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

Draw::TextureID Draw::loadTexture(std::string filename){
	mEngine->getConsole().print(std::string("load texture : ")+filename);
	
    SDL_Surface* imageSDL = SDL_LoadBMP(filename.c_str());
    if (imageSDL==NULL) {
		mEngine->getConsole().print("error file not exist");
		mEngine->getSystem().exitWithError();
		return 0;
    }
    
    GLuint id;
	glGenTextures(1, &id);
	
	glBindTexture(GL_TEXTURE_2D, id);
	
	GLenum formatInterne(0);
    GLenum format(0);
	
	if(imageSDL->format->BytesPerPixel == 3){
		// Format interne
        formatInterne = GL_RGB;
		
        // Format
        if(imageSDL->format->Rmask == 0xff)
            format = GL_RGB;
        else
            format = GL_BGR;
    }else if(imageSDL->format->BytesPerPixel == 4)
    {    
        // Format interne
        formatInterne = GL_RGBA;

        // Format
        if(imageSDL->format->Rmask == 0xff)
            format = GL_RGBA;
        else
            format = GL_BGRA;
    }else{
		mEngine->getConsole().print("not supported texture");
		mEngine->getSystem().exitWithError();
		return 0;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageSDL->w, imageSDL->h, 0, format, GL_UNSIGNED_BYTE, imageSDL->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glBindTexture(GL_TEXTURE_2D, 0);
	
	return id;
}

void Draw::setTexture(TextureID id)
{
	if(id!=0){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, id);
	}else{
		glDisable(GL_TEXTURE_2D);
	}
}

