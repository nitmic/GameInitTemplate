#pragma once
#include <memory>
#include <vector>
#include "ShootingObject.h"

class IScene{
public:
	virtual IScene * step() = 0;
	virtual void draw() = 0;
};

class ShootingScene : public IScene{
public:
	IScene * step();
	void draw();
private:
	std::vector<std::shared_ptr<IEnemy>> m_pEnemies;
	std::vector<std::shared_ptr<IDrawer>> m_pDrawers;
	std::vector<std::shared_ptr<OwnVehicle>> m_pPlayers;
	std::vector<std::shared_ptr<IBullet>> m_pEnemyBullets;
	std::vector<std::shared_ptr<IBullet>> m_pMyBullets;

};