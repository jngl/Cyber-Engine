#pragma once

#include <vector>
#include <fstream>

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

class Image 
{
public:
    Image(unsigned int width, unsigned int height);
    
    math::Vector3f& getPixelRef(unsigned int x, unsigned int y);
    
    unsigned int getWidth();
    unsigned int getHeight();
    
    math::Vector2f getSize();
    
    void save(const char* filename);
    
private:
    std::vector<math::Vector3f> mData;
    unsigned int mWidth;
    unsigned int mHeight;
};
