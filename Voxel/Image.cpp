#include "Image.hpp"

#include <iostream>
#include <cassert>

Image::Image(unsigned int width, unsigned int height):
mWidth(width),
mHeight(height)
{
    mData.resize(width*height);
}

glm::vec3& Image::getPixelRef(unsigned int x, unsigned int y){
    assert(x<mWidth && y<mHeight);
    return mData[y*mWidth + x];
}

unsigned int Image::getWidth(){
    return mWidth;
}
    
glm::vec2 Image::getSize(){
    return glm::vec2(mWidth, mHeight);
}

unsigned int Image::getHeight(){
    return mHeight;
}

void Image::save(const char* filename){
    std::ofstream file (filename, std::ofstream::out);
    
    file<<"P3"<<std::endl;
    file<<mWidth<<" "<<mHeight<<std::endl;
    file<<"255"<<std::endl;
    
    for(int y(mHeight-1); y>=0; --y){
        for(int x(0); x<mWidth; ++x){
            glm::vec3& color = getPixelRef(x, y);
            color = glm::max(color, glm::vec3(0.f));
                file<<glm::floor(color.x)<<" "<<glm::floor(color.y)<<" "<<glm::floor(color.z)<<" ";
        }
        file<<std::endl;
    }
}
