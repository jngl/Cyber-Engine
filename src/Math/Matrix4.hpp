#pragma once

#include <cmath>

#include "Vector3.hpp"

namespace math
{
    template<class T>
    struct Matrix4
    {
        void setIdentity(){
            memset(this, 0, sizeof(Matrix4<T>));

            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
        }
        
        Matrix4<T> operator*(const Matrix4<T>& t) const{
            Matrix4<T> r;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    r.m[i][j] = m[0][j]*t.m[i][0] + m[1][j]*t.m[i][1] + m[2][j]*t.m[i][2] + m[3][j]*t.m[i][3];
                }
            }
            return r;
        }
        
        Matrix4<T> operator*=(const Matrix4<T>& t){
            *this = (*this)*t;
            return *this;
        }

        void projectOrthographic(float left, float right, float bottom, float top, float near, float far){
            setIdentity();

            float XD = right - left;
            float YD = top - bottom;
            float ZD = far - near;

            m[0][0] = 2.0f / XD;
            m[1][1] = 2.0f / YD;
            m[2][2] = -2.0f / ZD;

            m[3][0] = -(right + left) / XD;
            m[3][1] = -(top + bottom) / YD;
            m[3][2] = -(far + near) / ZD;
        }

        void projectPerspective(float FOV, float aspectRatio, float near, float far){
            float tanThetaOver2 = tan(FOV * (float)M_PI / 360);
            setIdentity();

            // X and Y scaling
            m[0][0] = 1/tanThetaOver2;
            m[1][1] = aspectRatio/tanThetaOver2;

            // Z coordinate makes z -1 when we're on the near plane and +1 on the far plane
            m[2][2] = (near + far)/(near - far);
            m[3][2] = 2 * near * far / (near - far);

            // W = -1 so that we have [x y z -z], a homogenous vector that becomes [-x/z -y/z -1] after division by w.
            m[2][3] = -1;

            // Must zero this out, the identity has it as 1.
            m[3][3] = 0;

            return m;
        }
        
        void setTranslation(const Vector3<T>& vecPos){
            setIdentity();
            m[3][0] = vecPos.x;
            m[3][1] = vecPos.y;
            m[3][2] = vecPos.z;
        }
        
        void addTranslation(const Vector3<T>& v){
            Matrix4<T> r;
            r.SetTranslation(v);
            (*this) *= r;
            return *this;
        }

        void setScale(const Vector3<T>& vecScale)
        {
            setIdentity();
            m[0][0] = vecScale.x;
            m[1][1] = vecScale.y;
            m[2][2] = vecScale.z;
        }
        
        void addScale(const Vector3<T>& vecScale){
            Matrix4<T> r;
            r.setScale(vecScale);
            (*this) *= r;
            return *this;
        }

        void setRotation(float flAngle, const Vector3<T>& v){
            setIdentity();
            float x = v.x;
            float y = v.y;
            float z = v.z;

            float c = cos(flAngle*(float)M_PI/180);
            float s = sin(flAngle*(float)M_PI/180);
            float t = 1-c;

            m[0][0] = x*x*t + c;
            m[1][0] = x*y*t - z*s;
            m[2][0] = x*z*t + y*s;

            m[0][1] = y*x*t + z*s;
            m[1][1] = y*y*t + c;
            m[2][1] = y*z*t - x*s;

            m[0][2] = z*x*t - y*s;
            m[1][2] = z*y*t + x*s;
            m[2][2] = z*z*t + c;
        }
        
        void addRotation(float flAngle, const Vector3<T>& v){
            Matrix4<T> r;
            r.setRotation(flAngle, v);
            (*this) *= r;
            return *this;
        }
        
        T m[4][4];
    };
    
    
    
    typedef Matrix4<float> Matrix4f;
}
