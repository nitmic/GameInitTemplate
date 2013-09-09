#pragma once
#include "MDA.h"
#include <Percentage.h>
#include "GLAS.h"


class Air;
class Life;
class JetAgent;
class RCSAgent;
class Player;

class Astronaut : public I3DAgent{
public:
	bool isAlive();
	Astronaut();
	Astronaut(std::shared_ptr<Player> & pModel);
	Glas::Vector3f getPosition();
	Glas::Quaternion getAttitude();
	
	void thrust(
		const std::shared_ptr<JetAgent> & jetL,
		const std::shared_ptr<JetAgent> & jetR,
		const std::shared_ptr<RCSAgent> & jetRCS
	);

	void step();
	Air getAir();
	Life getLife();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};

class AstronautDrawer : public IDrawer{
public:
	AstronautDrawer();
	AstronautDrawer(std::shared_ptr<Astronaut> agent);
	bool isVisible();
	void draw();
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};


class PlayerMeterDrawer : public IDrawer{
public:
	bool isVisible();
	void draw();
private:
	//Scene m_pScene; Drawer‚ÍmodelˆÈŠO‚É‚àˆË‘¶‚µ‚½‚Ù‚¤‚ª‚æ‚¢‚©‚à
	std::shared_ptr<Player> m_pModel;
};




///////////////        Other         //////////////



class Air{
public:
	Air() : m_rest(1){};
	bool isEmpty();
private:
	Percent m_rest;
};

class Life{
public:
	Life() : m_rest(1){};
	bool isEmpty();
private:
	Percent m_rest;
};
