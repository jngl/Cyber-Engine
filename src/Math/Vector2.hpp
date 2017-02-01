#pragma once

namespace math
{
    template<class T>
    struct Vector2
    {
        T x, y;
		
		Vector2():
			x(0.f),
			y(0.f)
		{
		}
		
		Vector2(T px, T py):
			x(px),
			y(py)
		{
		}
        
        Vector2<T> operator-(const Vector2<T>& b) const{
            return Vector2<T>{x-b.x, y-b.y};
        }
        
        Vector2<T> operator-(const T& b) const{
            return Vector2<T>{x-b, y-b};
        }
        
         Vector2<T> operator-() const{
            return Vector2<T>{-x, -y,};
        }
        
        Vector2<T> operator+(const Vector2<T>& b) const{
            return Vector2<T>{x+b.x, y+b.y};
        }
        
        Vector2<T> operator * (const T scale){
		  return Vector2<T>{x*scale, y*scale};
		}
		
		Vector2<T> operator/ (const T scale){
		  return Vector2<T>{x/scale, y/scale};
		}
		
		Vector2<T> operator* (const Vector2<T>& right){
			return Vector2<T>{x*right.x, y*right.y};
		}
		
		Vector2<T> operator/ (const Vector2<T>& right){
			return Vector2<T>{x/right.x, y/right.y};
		}
		
		Vector2<T>& operator+=(const Vector2<T>& right){
			x+=right.x;
			y+=right.y;
			return *this;
		}
		
		Vector2<T>& operator-=(const Vector2<T>& right){
			x-=right.x;
			y-=right.y;
			return *this;
		}
		
		Vector2<T>& operator*=(const Vector2<T>& right){
			x*=right.x;
			y*=right.y;
			return *this;
		}
		
		Vector2<T>& operator/=(const Vector2<T>& right){
			x/=right.x;
			y/=right.y;
			return *this;
		}
        
        T getDotProduct(const Vector2<T>& t) const {
            return x*t.x + y*t.y;
		}
    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
}
