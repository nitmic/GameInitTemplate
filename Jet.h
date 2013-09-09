#pragma once
#include "GLAS.h"
#include "MDA.h"



/*
*@class JetAgent
*/

class JetAgent : public I3DAgent{
public:
	JetAgent();
	bool isAlive();
	void step(){};
	void thrust(Glas::Vector3f direction);
	void Join(
		std::shared_ptr<I3DAgent> agent,
		Glas::Vector3f offset=Glas::Vector3f(0,0,0)
	);
	Glas::Vector3f getPropellant();
	Glas::Quaternion getAttitude();
	Glas::Vector3f getPosition();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

class JetDrawer : public IDrawer{
public:
	JetDrawer();
	JetDrawer(std::shared_ptr<JetAgent> & agent);
	bool isVisible();
	void draw();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};


/*
*@class RCSAgent
*/

class RCSAgent : public I3DAgent{
public:
	RCSAgent();
	bool isAlive();
	void step();
	
	void Join(
		std::shared_ptr<I3DAgent> agent,
		Glas::Vector3f offset=Glas::Vector3f(0,0,0)
	);
	void rolling(Glas::Vector3f direction);

	Glas::Quaternion getRolling();
	Glas::Quaternion getAttitude();
	Glas::Vector3f getPosition();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};


class RCSDrawer : public IDrawer{
public:
	RCSDrawer();
	RCSDrawer(std::shared_ptr<RCSAgent> & agent);
	bool isVisible();
	void draw();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};
