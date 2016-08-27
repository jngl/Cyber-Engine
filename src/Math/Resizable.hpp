#pragma once

namespace math {
	template<class T>
	class Resizable : public Object {
	public:
		T getHeight() const {
			return mHeight;
		}

		void setHeight(T height) {
			mHeight = height;
		}

		T getWidth() const {
			return mWidth;
		}

		void setWidth(T width) {
			mWidth = width;
		}

		Vec2<T> getSize(){
			return Vec2<T>(mWidth, mHeight);
		}

		void setSize(Vec2<T> v){
			mWidth=v.x;
			mHeight=v.y;
		}

		void setSize(T width, T height){
			mWidth = width;
			mHeight = height;
		}

	private:
		T mWidth;
		T mHeight;
	};
} /* namespace ge */
#endif /* RRESIZABLE_HPP_ */
