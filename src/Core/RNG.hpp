#pragma once

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
        
    private:
        std::default_random_engine mGenerator;
    };
    
    
    extern RNG mRNG;
}
