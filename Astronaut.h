#pragma once
#include "MDA.h"


class Player;

class Astronaut : public IAgent{
public:
	bool isAlive();
	void step();
private:
	float radius;
	std::shared_ptr<Player> m_pModel;
};

class AstronautDrawer : public IDrawer{
public:
	AstronautDrawer();
	AstronautDrawer(std::shared_ptr<Player> model);
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