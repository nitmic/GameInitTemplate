#include "Camera.h"
#include "MDA.h"

struct TPSCamera::Impl{
	Impl() : distance(4){};
	std::shared_ptr<I3DAgent> target;
	Glas::Quaternion attitude;
	float                   distance;
	unsigned int            cameraIndex;
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
	auto p = __impl__->target->getPosition();
	auto direction = __impl__->attitude * Glas::Vector3f(0,0,1);
	return p - direction.normalize() * __impl__->distance;
}


float TPSCamera::getDistance() const{
	return __impl__->distance;
}

Glas::Quaternion TPSCamera::getAttitude() const{
	return __impl__->attitude;
}

void TPSCamera::setAttitude(Glas::Quaternion & q){
	__impl__->attitude = q;
}

void TPSCamera::setDistance(float d){
	__impl__->distance = d;
}

void TPSCamera::normalize(){
	setAttitude(Glas::Quaternion(0.5, 0, 0) * __impl__->target->getAttitude());
}

void TPSCamera::step(){}