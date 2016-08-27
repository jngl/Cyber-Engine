#pragma once

//https://github.com/RobertBeckebans/RBDOOM-3-BFG/blob/master/neo/idlib/math/Angles.

#include "Angle2.hpp"


namespace math
{
    template<class T>
    class Angle3
    {
    public:
        Angle2<T> pitch;
        Angle2<T> yaw;
        Angle2<T> roll;
        
        Angle3(){
        }
        
        Angle3(T pPitch, T pYaw, T pRoll ):
            pitch(pPitch),
            yaw(pYaw),
            roll(pRoll)
        {
        }
        
        void set( T pPitch, T pYaw, T pRoll ){
            pitch = pPitch;
            yaw = pYaw;
            roll = pRoll;
        }
    };
    
    typedef Angle3<float> Angle3f;
}
