#pragma once

#include <vector>
#include <fstream>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

class Image 
{
public:
    Image(unsigned int width, unsigned int height);
    
    glm::vec3& getPixelRef(unsigned int x, unsigned int y);
    
    unsigned int getWidth();
    unsigned int getHeight();
    
    glm::vec2 getSize();
    
    void save(const char* filename);
    
private:
    std::vector<glm::vec3> mData;
    unsigned int mWidth;
    unsigned int mHeight;
};
