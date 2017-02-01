#include "Image.hpp"

#include <iostream>
#include <cassert>
#include <cmath>

Image::Image(unsigned int width, unsigned int height):
mWidth(width),
mHeight(height)
{
    mData.resize(width*height);
}

math::Vector3f& Image::getPixelRef(unsigned int x, unsigned int y){
    assert(x<mWidth && y<mHeight);
    return mData[y*mWidth + x];
}

unsigned int Image::getWidth(){
    return mWidth;
}
    
math::Vector2f Image::getSize(){
    return {static_cast<float>(mWidth), static_cast<float>(mHeight)};
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
            math::Vector3f& color = getPixelRef(x, y);
            color = math::Vector3f::max(color, math::Vector3f{0.f, 0.f, 0.f});
                file<<math::floor(color.x)<<" "<<math::floor(color.y)<<" "<<math::floor(color.z)<<" ";
        }
        file<<std::endl;
    }
}
