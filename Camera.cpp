#include "Camera.h"
#include "MDA.h"
#include <AngleUnit.h>
#include <RingBuffer.hpp>
#include "Debug.h"
#include <iomanip>
#include <numeric>

struct TPSCamera::Impl{
	Impl() : distance(15) {};
	std::shared_ptr<I3DAgent> target;

	Glas::Quaternion attitude;
	float                   distance;
	unsigned int            cameraIndex;
	TUL::RingBuffer<Glas::Vector3f,30> targetDisplacement;
	TUL::RingBuffer<float,30> acceleration;
};

TPSCamera::TPSCamera(){
	__impl__ = std::make_shared<Impl>();
};

TPSCamera::TPSCamera(std::shared_ptr<I3DAgent> target){
	__impl__ = std::make_shared<Impl>();
	setTarget(target);
};

void TPSCamera::setTarget(const std::shared_ptr<I3DAgent> & target){
	__impl__->target = target;
	normalize();
}


Glas::Vector3f TPSCamera::getPosition() const{
	auto direction = __impl__->attitude * Glas::Vector3f(0,0,1);
	auto lookAt = getLookAt() + __impl__->target->getAttitude() * Glas::Vector3f(0,3,5);
	
	auto curVelocity = __impl__->targetDisplacement.prev(0) - __impl__->targetDisplacement.prev(1);
	auto preVelocity = __impl__->targetDisplacement.prev(1) - __impl__->targetDisplacement.prev(2);
	/*__impl__->acceleration.update(curVelocity.getLength() - preVelocity.getLength());

	float acceleration = 0;
	for(auto it=__impl__->acceleration.begin(); it!=__impl__->acceleration.end(); it++){
		acceleration += *it;
	}*/
	auto acceleration = 0; //curVelocity.getLength() - preVelocity.getLength();
	auto velocity = __impl__->targetDisplacement.prev(0) - __impl__->targetDisplacement.prev(21);


	return lookAt - direction.normalize() * (__impl__->distance + acceleration) - velocity/3;
}

Glas::Vector3f TPSCamera::getLookAt() const{
	return __impl__->target->getPosition();
}

float TPSCamera::getDistance() const{
	return __impl__->distance;
}

Glas::Quaternion TPSCamera::getAttitude() const{
	return __impl__->attitude;
}

void TPSCamera::setAttitude(Glas::Quaternion & q){
	__impl__->attitude = q;
	__impl__->attitude.normalize();
}

void TPSCamera::setDistance(float d){
	if(d>40) return;
	if(d<8) return;
	__impl__->distance = d;
}

void TPSCamera::normalize(){
	setAttitude(__impl__->target->getAttitude());
}

void TPSCamera::step(){
	__impl__->targetDisplacement.update(
		__impl__->target->getPosition()
	);
}
void TPSCamera::rotate(TUL::Degree deg, Glas::Vector3f v){
	Glas::Quaternion attitude;
	attitude.fromAngleAxis(deg, v.normalize());
	attitude.normalize();
	setAttitude(attitude * __impl__->attitude);
}