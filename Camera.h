#pragma once
#include <memory>

class ICamera{
public:
	virtual void step() = 0;
	virtual void transform() = 0;

	virtual Blas::Vector3f getLookAt() = 0;
	virtual Blas::Vector3f getPosition() = 0;
	virtual Blas::Vector3f getVirtical() = 0;
};

/* –¢ŽÀ‘• */
class EditCamera : public ICamera{
public:
	void step();
	Blas::Vector3f getLookAt();
	Blas::Vector3f getPosition();
	Blas::Vector3f getVirtical();
};

class I3DModel;

class TPSCamera : public ICamera{
public:
	void step();
	Blas::Vector3f getLookAt();
	Blas::Vector3f getPosition();
	Blas::Vector3f getVirtical();
	float getDistance();

	void setTarget(std::shared_ptr<I3DModel> target);
	void setVirtical(Blas::Vector3f v);
	void setDirection(Blas::Vector3f v);
	void setDistance(float d);
	void rotate(int amount);

	TPSCamera();
	TPSCamera(std::shared_ptr<I3DModel> target);
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

