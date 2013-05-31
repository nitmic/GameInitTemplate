#pragma once
#include <memory>
#include <vector>
#include "ShootingObject.h"

class IScene;
typedef IScene * NextScene;

class IScene{
public:
	virtual NextScene step() = 0;
	virtual void draw() = 0;


};

class ShootingScene : public IScene{
public:
	NextScene step();
	void draw();
private:
	typedef std::shared_ptr<OwnVehicle> Player;
	typedef std::vector<Player> Players;
	Players m_pPlayers;

	typedef std::shared_ptr<IEnemy> Enemy;
	typedef std::vector<Enemy> Enemies;
	Enemies m_pEnemies;
	
	typedef std::shared_ptr<IDrawer> Drawer;
	typedef std::vector<Drawer> Drawers;
	Drawers m_pDrawers;
	
	typedef std::shared_ptr<IBullet> Bullet;
	typedef std::vector<Bullet> Bullets;
	Bullets m_pEnemyBullets;
	Bullets m_pMyBullets;

};