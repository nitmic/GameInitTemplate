#pragma once
#include "MDA.h"

class IShootingAgent : public IAgent{
public:
	virtual void hit(IShootingAgent * object) = 0;
};

class IEnemy : public IShootingAgent{
public:
	virtual void shot(IShootingAgent * object) = 0;
};

class IBullet : public IShootingAgent{
public:
	virtual void shot(IShootingAgent * object) = 0;
};

class Player : public IModel{
public:
	bool isValid();
};

class OwnVehicle : public IShootingAgent{
public:
	bool isVisible();
	void draw();
private:
	std::weak_ptr<Player> player;
};

class OwnVehicleDrawer : public IDrawer{
public:
	bool isAlive();
	void step();
private:
	std::weak_ptr<Player> player;
};