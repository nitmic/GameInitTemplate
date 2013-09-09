#pragma once
#include "MDA.h"
#include "GLAS.h"

class IDebri : public I3DAgent{
};

class Meteor1 : public IDebri{
public:
	Meteor1();
	Meteor1(Glas::Vector3f pos, Glas::Vector3f rotate, Glas::Vector3f velocity);
	bool isAlive(){return true;};
	Glas::Vector3f getPosition();
	Glas::Quaternion getAttitude();
	void step();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

class Meteor1Drawer : public IDrawer{
public:
	Meteor1Drawer();
	Meteor1Drawer(std::shared_ptr<Meteor1> agent);
	bool isVisible();
	void draw();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};



class Meteor2 : public IDebri{
public:
	Meteor2();
	Meteor2(Glas::Vector3f pos, Glas::Vector3f rotate, Glas::Vector3f velocity);
	bool isAlive(){return true;};
	Glas::Vector3f getPosition();
	Glas::Quaternion getAttitude();
	void step();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

class Meteor2Drawer : public IDrawer{
public:
	Meteor2Drawer();
	Meteor2Drawer(std::shared_ptr<Meteor2> agent);
	bool isVisible();
	void draw();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};
