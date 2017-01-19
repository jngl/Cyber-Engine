#pragma once

namespace math
{
    template<class T>
    struct Vector2
    {
        T x, y;
    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
}
