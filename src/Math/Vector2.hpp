#pragma once

#include <string>

namespace math {
    
	template <class T2>
	class Vec2
	{
	  public:
		Vec2(T2 X = 0, T2 Y = 0)
		{
		  x = X;
		  y = Y;
		}

		Vec2(const Vec2<T2> &source)
		{
		  x = source.x;
		  y = source.y;
		}

		Vec2<T2> &operator = (const Vec2 &right){
		  x = right.x;
		  y = right.y;
		  return *this;
		}

		inline Vec2<T2> operator + (const Vec2<T2> &right)
		{
		  return Vec2<T2>(right.x + x, right.y + y);
		}

		inline Vec2<T2> operator - (const Vec2<T2> &right){
		  return Vec2<T2>(-right.x + x, -right.y + y);
		}


		inline Vec2<T2> operator * (const T2 scale){
		  return Vec2<T2>(x*scale, y*scale);
		}
                
                inline Vec2<T2> operator * (const Vec2<T2> vec){
		  return Vec2<T2>(x*vec.x, y*vec.y);
		}

		inline Vec2<T2>  operator / (const T2 scale){
		  if(scale) 
			return Vec2<T2>(x/scale, y/scale);
		  return Vec2<T2>(0, 0);
		}

		inline Vec2<T2> &operator += (const Vec2<T2> &right)
		{
		  x+=right.x;
		  y+=right.y;
		  return *this;
		}

		inline Vec2<T2> &operator -= (const Vec2<T2> &right)
		{
		  x-=right.x;
		  y-=right.y;
		  return *this;
		}

		inline Vec2<T2> &operator *= (const T2 scale)
		{
		  x*=scale;
		  y*=scale;
		  return *this;
		}

		inline Vec2<T2> &operator /= (const T2 scale){
		  if(scale)
		  {
			x /=scale;
			y /=scale;
		  }
		  return *this;
		}

		inline operator const T2*() const { return &x; }
		inline operator T2*()             { return &x; }   

		  inline const T2  operator[](int i) const { return ((T2*)&x)[i]; }
		  inline       T2 &operator[](int i)       { return ((T2*)&x)[i]; }

		bool operator == (const Vec2<T2> &right)
		{
		  return (x == right.x &&
				  y == right.y);
		}

		bool operator != (const Vec2<T2> &right)
		{
		  return !(x == right.x &&
				   y == right.y );
		}

		void set(T2 nx, T2 ny)
		{
		  x = nx;
		  y = ny;
		}

		inline void clamp(T2 min, T2 max)
		{
		  x = x > max ? max : x < min ? min  : x;
		  y = y > max ? max : y < min ? min  : y;
		}

		virtual std::string toString(){
			std::string str("Vec2( x : ");
			str+=std::to_string(x);
			str+=", y : ";
			str+=std::to_string(y);
			str+=")";
			return str;
		}

		T2 x, y;
	};

	typedef Vec2<int> 		       Vec2i;
	typedef Vec2<unsigned int>     Vec2ui;
	typedef Vec2<float>            Vec2f;
	typedef Vec2<double>           Vec2d;
}
