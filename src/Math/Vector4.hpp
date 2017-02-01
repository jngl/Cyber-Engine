#pragma once

namespace math
{
    template<class T>
    struct Vector4
    {
        T x, y, z, w;
		
		Vector4():
			x(0.f),
			y(0.f),
			z(0.f),
			w(0.f)
		{
		}
		
		Vector4(T px, T py, T pz, T pw):
			x(px),
			y(py),
			z(pz),
			w(pw)
		{
		}
    };
    
    typedef Vector4<float> Vector4f;
    typedef Vector4<int> Vector4i;
}
