#pragma once

#include "MathUtils.hpp"

namespace math
{
    template<class T>
    struct Vector3
    {
        T x, y, z;
		
		Vector3():
			x(0.f),
			y(0.f),
			z(0.f)
		{
		}
		
		Vector3(T px, T py, T pz):
			x(px),
			y(py),
			z(pz)
		{
		}
        
        Vector3<T> operator-(const Vector3<T>& b) const{
            return Vector3<T>{x-b.x, y-b.y, z-b.z};
        }
        
         Vector3<T> operator-() const{
            return Vector3<T>{-x, -y, -z};
        }
        
        Vector3<T> operator+(const Vector3<T>& b) const{
            return Vector3<T>{x+b.x, y+b.y, z+b.z};
        }
        
        Vector3<T> operator * (const T scale){
		  return Vector3<T>{x*scale, y*scale, z*scale};
		}
		
		Vector3<T> operator/ (const T scale){
		  return Vector3<T>{x/scale, y/scale, z/scale};
		}
		
		Vector3<T> operator* (const Vector3<T>& right){
			return Vector3<T>{x*right.x, y*right.y, z*right.z};
		}
		
		Vector3<T> operator/ (const Vector3<T>& right){
			return Vector3<T>{x/right.x, y/right.y, z/right.z};
		}
		
		Vector3<T>& operator+=(const Vector3<T>& right){
			x+=right.x;
			y+=right.y;
			z+=right.z;
			return *this;
		}
		
		Vector3<T>& operator-=(const Vector3<T>& right){
			x-=right.x;
			y-=right.y;
			z-=right.z;
			return *this;
		}
		
		Vector3<T>& operator*=(const Vector3<T>& right){
			x*=right.x;
			y*=right.y;
			z*=right.z;
			return *this;
		}
		
		Vector3<T>& operator*=(const T& right){
			x*=right;
			y*=right;
			z*=right;
			return *this;
		}
		
		Vector3<T>& operator/=(const Vector3<T>& right){
			x/=right.x;
			y/=right.y;
			z/=right.z;
			return *this;
		}
        
        void set(T px, T py, T pz){
            x=px;
            y=py;
            z=pz;
        }
        
        void setAllAxes(T v){
            x=v;
            y=v;
            z=v;
        }
        
        T getLengthSquared() const {
            return  x*x + y*y + z*z;
            
        }
		T getLength() const {
            return sqrtf(x*x + y*y + z*z); 
        }
        
        Vector3<T>& normalize(){
            T length  = getLength();
			
            if(!length){
                set(0,0,0);
                return *this;
            }
            x/=length;
            y/=length;
            z/=length;
            return *this;
		}
		
		T getDotProduct(const Vector3<T>& t) const {
            return x*t.x + y*t.y + z*t.z;
		}
        
        Vector3<T> getCrossProduct(const Vector3<T>& v) const{
			return {y * v.z - z * v.y,
				v.x * z - v.z * x,
				x * v.y - y * v.x};
		}
		
		Vector3<T> getFloor(){
			return Vector3<T>{floor(x), floor(y), floor(z)};
		}
		
		Vector3<T> getSign(){
			return Vector3<T>{sign(x), sign(y), sign(z)};
		}
        
        static Vector3<T> max(Vector3<T> a, Vector3<T> b){
            return Vector3<T>{  a.x>b.x?a.x:b.x, 
                                                a.y>b.y?a.y:b.y, 
                                                a.z>b.z?a.z:b.z};
        }
        
        static Vector3<T> mix(Vector3<T> a, Vector3<T> b, T v){
            return Vector3<T>{math::mix(a.x, b.x, v), math::mix(a.y, b.y, v), math::mix(a.z, b.z, v)};
        }
    };
    
    
    
    typedef Vector3<float> Vector3f;
    typedef Vector3<int> Vector3i;
}
