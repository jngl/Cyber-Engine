#pragma once

#include <Math/Vec2.hpp>
#include <Core/Error.hpp>

namespace core {
	template<class T>
	class Array2D {
	public:
		Array2D():
			mData(nullptr){
		}

		virtual ~Array2D(){
			if(mData!=nullptr){
				delete[] mData;
			}
		}

		void create(Vec2ui size){
			mSize=size;
			mData=new T[mSize.x*mSize.y];
		}

		void create(unsigned int x, unsigned int y){
			create(Vec2ui(x, y));
		}

		void destroy(){
			delete[] mData;
		}

		T& at(unsigned int x, unsigned int y){
			if(x>=mSize.x || y>=mSize.y)
				throw Error("Array2D::at() : out of array");
			return mData[y*mSize.x+x];
		}

		T& at(Vec2ui index){
			return at(index.x, index.y);
		}

		void set(unsigned int x, unsigned int y, T value){
			if(x>=mSize.x || y>=mSize.y)
				throw Error("Array2D::set() : out of array");
			mData[y*mSize.x+x]=value;
		}

		void set(Vec2ui index, T value){
			set(index.x, index.y, value);
		}

		Vec2ui getSize(){
			return mSize;
		}

	private:
		T* mData;
		Vec2ui mSize;
	};
} /* namespace core */

