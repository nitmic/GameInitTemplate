#include "Camera.h"
#include "MDA.h"

struct TPSCamera::Impl{
	Impl() : distance(8){};
	std::shared_ptr<I3DModel> target;
	Blas::Vector3f    direction;
	Blas::Vector3f    verticalDirection;
	float                   distance;
	unsigned int            cameraIndex;
};

TPSCamera::TPSCamera(){
	__impl__ = std::make_shared<Impl>();
	__impl__->verticalDirection[0] = 0;
	__impl__->verticalDirection[1] = 1;
	__impl__->verticalDirection[2] = 0;
	__impl__->direction[0] = 0;
	__impl__->direction[1] = 0;
	__impl__->direction[2] = 1;
};

TPSCamera::TPSCamera(std::shared_ptr<I3DModel> target){
	__impl__ = std::make_shared<Impl>();
	__impl__->target = target;
};

void TPSCamera::setTarget(std::shared_ptr<I3DModel> target){
	__impl__->target = target;
}

Blas::Vector3f TPSCamera::getLookAt(){
	auto pos = __impl__->target->getPosition();
	return pos + __impl__->direction + __impl__->verticalDirection;
}

Blas::Vector3f TPSCamera::getPosition(){
	return getLookAt() - __impl__->direction * __impl__->distance + __impl__->verticalDirection * 3;
}

float TPSCamera::getDistance(){
	return __impl__->distance;
}

Blas::Vector3f TPSCamera::getVirtical(){
	return __impl__->verticalDirection;
}

void TPSCamera::rotate(int amount){
	int direction = amount>0 ? 1 : -1;
	amount = amount * direction;
	for(unsigned int i=0;i<amount;i++){
		Blas::Vector3f x = Blas::cross_prod(__impl__->verticalDirection,__impl__->direction);
		__impl__->direction = Blas::normalize3(__impl__->direction + x*direction);
	}
}

void TPSCamera::setVirtical(Blas::Vector3f v){
	__impl__->verticalDirection = v;
}

void TPSCamera::setDirection(Blas::Vector3f v){
	__impl__->direction = v;
}

void TPSCamera::setDistance(float d){
	__impl__->distance = d;
}


void TPSCamera::step(){}