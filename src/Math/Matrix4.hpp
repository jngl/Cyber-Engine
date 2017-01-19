#pragma once

namespace math
{
    template<class T>
    struct Matrix4
    {
        T values[16];
    };
    
    typedef Matrix4<float> Matrix4f;
}
