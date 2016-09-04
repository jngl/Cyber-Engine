#pragma once

//https://github.com/RobertBeckebans/RBDOOM-3-BFG/blob/master/neo/idlib/math/Angles.

#include "Angle2.hpp"
#include "Vector3.hpp"

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
        
        Vec3<T> toDirection(){
            Vec3<T> dir;
            dir.x = cos(pitch.getRadian()) * cos(yaw.getRadian());
            dir.y = sin(pitch.getRadian());
            dir.z = cos(pitch.getRadian()) * sin(yaw.getRadian());
            return dir;
        }
    };
    
    typedef Angle3<float> Angle3f;
}
