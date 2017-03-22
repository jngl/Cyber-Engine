#pragma once

#include <string>

#include "Rect.hpp"

class Engine;

class Draw
{
public:
	Draw(Engine* engine);
	
	typedef unsigned int TextureID;
	
	void clear(float r, float g, float b);
	
	void ortho(float left, float right, float bottom, float top, float near_val, float far_val);
	
	void rect(float x, float y, float w, float h);//the x & y location of the rectangle's upper left corner
	void rect(Rectf r);
	
	void setColor(float r, float g, float b);
	
	TextureID loadTexture(std::string filename);
	
	void setTexture(TextureID id);
	
private:
	Engine* mEngine;
};
