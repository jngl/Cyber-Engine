#pragma once

namespace math
{
    template<class T>
    struct Vector4
    {
        T x, y, z, w;
    };
    
    typedef Vector4<float> Vector4f;
    typedef Vector4<int> Vector4i;
}
