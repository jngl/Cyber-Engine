#pragma once

#include "../Math/Vector4.hpp"

#include <random>

namespace core
{
    class RNG
    {
    public:
        RNG();
        
        template<class T>
        T getReal(T from, T to){
            std::uniform_real_distribution<T> distribution(from,to);
            return distribution(mGenerator);
        }
        
        template<class T>
        math::Vec2<T> getVec2(T from, T to){
            return math::Vec2<T>(getReal<T>(from, to),
                                 getReal<T>(from, to));
        }
        
        template<class T>
        math::Vec3<T> getVec3(T from, T to){
            return math::Vec3<T>(getReal<T>(from, to),
                                 getReal<T>(from, to),
                                 getReal<T>(from, to)
                                );
        }
        
        template<class T>
        math::Vec4<T> getVec4(T from, T to){
            return math::Vec4<T>(getReal<T>(from, to),
                                 getReal<T>(from, to),
                                 getReal<T>(from, to),
                                 getReal<T>(from, to)
                                );
        }
        
    private:
        std::default_random_engine mGenerator;
    };
    
    
    extern RNG mRNG;
}
