#pragma once

namespace math
{
    template<class T>
    struct Vector3
    {
        T x, y, z;
    };
    
    typedef Vector3<float> Vector3f;
    typedef Vector3<int> Vector3i;
}
