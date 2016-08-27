#pragma once

#include <iostream>
#include "Vector3.hpp"

using namespace std;

namespace math {
	
	template <class type>
	class Vec4
	{
	  public:
		Vec4<type>(type X = 0, type Y = 0, type Z = 0, type W = 0)
		{
		  x = X;
		  y = Y;
		  z = Z;
		  w = W;
		}

		Vec4<type>(type XYZW)
		{
		  x =  
		  y =  
		  z =  
		  w = XYZW;
		}

		Vec4<type>(const Vec4<type> &source)
		{
		  x = source.x;
		  y = source.y;
		  z = source.z;
		  w = source.w;
		}
	 
		Vec4<type>(const Vec3<type> &source, const type W = 1)
		{
		  x = source.x;
		  y = source.y;
		  z = source.z;
		  w = W;
		}

		inline operator const type*() const { return &x; }
		inline operator type*() { return &x; }   

		  inline const type  operator[](int i) const { return ((type*)&x)[i]; }
		  inline       type &operator[](int i)       { return ((type*)&x)[i]; }
	 
		inline Vec4<type> &operator = (const Vec4<type> &source){
		  x = source.x;
		  y = source.y;
		  z = source.z;
		  w = source.w;
		  return *this;
		}

		inline Vec4<type> &operator = (const Vec3<type> &source)
		{
		  x = source.x;
		  y = source.y;
		  z = source.z;
		  w = 1.0f;
		  return *this;
		}

		inline Vec4<type> operator + (const Vec4<type> &right){
		  return Vec4<type>(right.x + x, right.y + y, right.z + z, right.w + w );
		}

		inline Vec4<type> operator - (const Vec4<type>  &right){
		  return Vec4<type>(-right.x + x, -right.y + y, -right.z + z, -right.w + w );
		}

		inline Vec4<type> operator * (const type scale){
		  return Vec4<type>(x*scale, y*scale, z*scale, w*scale);
		}

		inline Vec4<type> operator / (const type scale){
		   return scale ? Vec4<type>(x/scale, y/scale, z/scale, w/scale) : Vec4<type>(0, 0, 0, 0);
		}

		inline Vec4<type> &operator += (const Vec4<type> &right)
		{
		  x +=right.x;
		  y +=right.y;
		  z +=right.z;
		  w +=right.w;
		  return *this;
		}

		inline Vec4<type> operator -= (const Vec4<type> &right)
		{
		  x-=right.x;
		  y-=right.y;
		  z-=right.z;
		  w-=right.w;
		  return *this;
		}

		inline Vec4<type> clamp(const type min, const type max)
		{
		  x = x < min ? min : x > max ? max : x;
		  y = y < min ? min : y > max ? max : y;
		  z = z < min ? min : z > max ? max : z;
		  w = w < min ? min : w > max ? max : w;
		  return *this;
		}

		inline Vec4<type> operator *= (const type scale)
		{
		  x*=scale;
		  y*=scale;
		  z*=scale;
		  w*=scale;
		  return *this;
		} 

		inline Vec4<type> operator /= (const type scale)
		{
		  if(scale)
		  {
			x/=scale;
			y/=scale;
			z/=scale;
			w/=scale;
		  }
		  return *this;
		}

		inline bool operator == (const Vec4<type> &right){
		  return (x == right.x &&
				  y == right.y &&
				  z == right.z &&
				  w == right.w);
		}

		bool operator != (const Vec4<type> &right){
		  return !(x == right.x &&
				   y == right.y &&
				   z == right.z &&
				   w == right.w);
		}

		inline void set(type xyzw)
		{
		  x = 
		  y =  
		  z =  
		  w = xyzw;
		}

		inline void set(type nx, type ny, type nz, type nw)
		 {
		  x = nx;
		  y = ny;
		  z = nz;
		  w = nw;
		}

		inline void set(const Vec4<type>  & vec)
		{
		  x = vec.x;
		  y = vec.y;
		  z = vec.z;
		  w = vec.w;   
		}

		inline void set(const Vec3<type>  & vec, const type W = 1){
		  x = vec.x;
		  y = vec.y;
		  z = vec.z;
		  w = W;   
		}

		  friend ostream & operator<< ( ostream & out, const Vec4<type> & right){
		  return out << "Vec4( " << right.x
								   << ", "
								   << right.y
								   << ", "
								   << right.z
								   << ", "
								   << right.w
								   << ")\n";
		}

		type x, y, z, w;
	};

	typedef Vec4<int   > Vec4i;
	typedef Vec4<float > Vec4f;
	typedef Vec4<double> Vec4d;
}


