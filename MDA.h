#pragma once
#include "GLAS.h"

class IModel{
public:
	virtual bool isValid() = 0;
};

class IDrawer{
public:
	virtual bool isVisible() = 0;
	virtual void draw() = 0;
};

class IAgent{
public:
	virtual bool isAlive() = 0;
	virtual void step() = 0;
};


class I3DAgent : public IAgent{
public:
	virtual Glas::Vector3<float> getPosition() = 0;
	virtual Glas::Quaternion getAttitude() = 0;
};