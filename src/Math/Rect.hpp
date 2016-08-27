#pragma once
#include <Math/Vec2.hpp>

namespace math {
	template<class T>
	class Rect {
	public:
		/**
		 * \brief Default Constructor
		 */
		Rect():
			mX(0),
			mY(0),
			mWidth(0),
			mHeight(0){}
                        
                Rect(Vec2<T> pos, Vec2<T> size):
                        mX(pos.x),
                        mY(pos.y),
                        mWidth(size.x),
                        mHeight(size.y)
                {
                    
                }


		/**
		 * \brief constructor
		 * @param top
		 * @param button
		 * @param left
		 * @param right
		 */
		Rect(T x, T y, T width, T height):
			mX(x),
			mY(y),
			mWidth(width),
			mHeight(height){}

		Vec2<T> getCenter() const{
			return Vec2<T>(mX+(mWidth/2), mY+(mHeight/2));
		}

		virtual std::string toString(){
			std::string str("Rect(x : ");
			str+=std::to_string(mX);
			str+=", y : ";
			str+=std::to_string(mY);
			str+=", width : ";
			str+=std::to_string(mWidth);
			str+=", height : ";
			str+=std::to_string(mHeight);
			str+=")";
			return str;
		}

		T mX;
		T mY;
		T mWidth;
		T mHeight;
	};

	typedef Rect<float> Rectf;
	typedef Rect<int> Recti;
        typedef Rect<unsigned int> Rectui;
} /* namespace ge */
#endif /* RECT_H_ */
