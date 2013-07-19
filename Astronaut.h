#pragma once
#include "MDA.h"
#include <Percentage.h>
#include "GLAS.h"

class Player;


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

struct JetPower{
	JetPower(){
		std::fill(direction.begin(), direction.end(), 0);
		power = 0;
	}
	Glas::Vector3f direction;
	float power;
};


class Astronaut : public I3DAgent{
public:
	bool isAlive();
	Astronaut() : m_Attitude(0,0,0){};
	Glas::Vector3f getPosition();
	Glas::Quaternion getAttitude(){return m_Attitude;};
	
	void jetPropellant(JetPower jetL, JetPower jetR);

	void step();
	//void move(Blas::Vector3f v);
	Air getAir(){ return m_air;};
	Life getLife(){ return m_life;}
private:
	std::shared_ptr<Player> m_pModel;
private:
	Glas::Vector3f m_RotatePower;
	Glas::Vector3f m_SufferPower;
	Air m_air;
	Life m_life;
	Glas::Vector3f m_Pos;
	Glas::Quaternion m_Attitude;
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