#pragma once
#include "GLAS.h"

class ICamera{
public:
	virtual void step() = 0;
	virtual void transform() = 0; // �����Adapter�ɔC����
	
	virtual Glas::Quaternion getAttitude() const = 0;
	virtual Glas::Vector3f getPosition() const = 0;
};

/* ������ */
class EditCamera : public ICamera{
public:
	void step();
	Glas::Quaternion getAttitude() const;
	Glas::Vector3f getPosition() const;
};

class I3DAgent;

class TPSCamera : public ICamera{
public:
	void step();
	Glas::Quaternion getAttitude() const;
	Glas::Vector3f getPosition() const;
	float getDistance() const;

	void setTarget(const std::shared_ptr<I3DAgent> & target);
	void setDistance(float d);
	void setAttitude(Glas::Quaternion & q);

	void normalize();

	TPSCamera();
	TPSCamera(std::shared_ptr<I3DAgent> target);
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

