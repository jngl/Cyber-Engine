#pragma once

#include <cmath>

namespace math {
	template<class T>
	class Angle2 {
	public:
		Angle2():
			mAngle(0)
		{}
		virtual ~Angle2(){}

		void setRadian(T value){
			mAngle=value;
			if(mAngle<0 || mAngle>2*M_PI){
				mAngle=(double)fmod((double)mAngle, (double)2*M_PI);
			}
		}

		void setDegree(T value){
			setRadian(value*M_PI/180);
		}

		T getRadian(){
			return mAngle;
		}

		T getDegree(){
			return mAngle*180/M_PI;
		}

		void rotateRadian(T value){
			setRadian(mAngle+value);
		}

		void rotateDegree(T value){
			setRadian(mAngle+ (value*M_PI/180) );
		}

	private:
		T mAngle;//radian 0<=mAngle<PI*2
	};

	typedef Angle2<float> Angle2f;
	typedef Angle2<double> Angle2d;
} /* namespace ge */
