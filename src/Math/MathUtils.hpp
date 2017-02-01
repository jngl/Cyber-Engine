#pragma once

#include <cmath>
#include <algorithm>

namespace math
{
    template<class T>
    T mix(T x, T y, T a){
        return x*(1-a) + y*a;
    }
    
    template<class T>
    T fract(T v){
		T intpart;
		return std::modf(v, &intpart);
	}
	
	template<class T>
	T sign(T v){
		return v<static_cast<T>(0.f)?-1.0f:1.0f;
	}
	
	using std::floor;
	using std::cos;
	using std::sin;
	using std::max;
	using std::min;
	using std::abs;
	using std::sqrt;
}
