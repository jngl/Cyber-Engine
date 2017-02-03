#include <iostream>
#include <cassert>
#include "Math/Vector3.hpp"

void testVector3f(){
	std::cout<<"testVector3f"<<std::endl;
	
	math::Vector3f a;
	assert(a.x==0.f && a.y==0.f && a.z==0.f);
	
	math::Vector3f b(1.f, 2.f, 3.f);
	assert(b.x==1.f && b.y==2.f && b.z==3.f);
	
	math::Vector3f c = {4.f, 5.f, 6.f};
	assert(c.x==4.f && c.y==5.f && c.z==6.f);
	
	a = c - b;
	assert(a.x==3.f && a.y==3.f && a.z==3.f);
	
	b = -b;
	assert(b.x==-1.f && b.y==-2.f && b.z==-3.f);
	
	a = c + b;
	assert(a.x==3.f && a.y==3.f && a.z==3.f);
	
	a = c * 2.f;
	assert(a.x==8.f && a.y==10.f && a.z==12.f);
	
	a = a / 2.f;
	assert(a.x==4.f && a.y==5.f && a.z==6.f);
	
	a = a * b;
	assert(a.x==-4.f && a.y==-10.f && a.z==-18.f);
	
	a = a / b;
	assert(a.x==4.f && a.y==5.f && a.z==6.f);
	
	a += b;
	assert(a.x==3.f && a.y==3.f && a.z==3.f);
	
	a -= b;
	assert(a.x==4.f && a.y==5.f && a.z==6.f);
	
	a*=b;
	assert(a.x==-4.f && a.y==-10.f && a.z==-18.f);
	
	a*=2.f;
	assert(a.x==-8.f && a.y==-20.f && a.z==-36.f);
	
	a/=b;
	assert(a.x==8.f && a.y==10.f && a.z==12.f);
	
	a.set(1.f, 2.f, 3.f);
	assert(a.x==1.f && a.y==2.f && a.z==3.f);
	
	a.setAllAxes(1.f);
	assert(a.x==1.f && a.y==1.f && a.z==1.f);
	
	assert(a.getLengthSquared()==3.f);
	
	assert(a.getLength()==math::sqrt(3.f));
	
	a.normalize();
	assert(a.getLength()>0.99999f && a.getLength()<1.1111111);
	
	a.set(1.f, 3.f, -5.f);
	b.set(4.f, -2.f, -1.f);
	assert(a.getDotProduct(b)==3.f);
	
	a.set(2.f, 3.f, 4.f);
	b.set(5.f, 6.f, 7.f);
	a = a.getCrossProduct(b);
	
	a.set(1.3f, 5.7f, 45.9f);
	a = a.getFloor();
	assert(a.x==1.f && a.y==5.f && a.z==45.f);
	
	a.y=-45;
	a = a.getSign();
	assert(a.x==1.f && a.y==-1.f && a.z==1.f);
	
	a.set(0.f, 2.f, 4.f);
	b.set(-1.f, 2.f, 5.f);
	a = math::Vector3f::max(a, b);
	assert(a.x==0.f && a.y==2.f && a.z==5.f);
	
	
	
}

int main(){
	std::cout<<"Test"<<std::endl;
	testVector3f();
	return 0;
}
