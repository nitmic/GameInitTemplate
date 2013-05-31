#include "Scene.h"
#include "MDAUtility.hpp"
#include "HitCheck.hpp"

void ShootingScene::draw(){
	drawing(m_pDrawers);
}

IScene * ShootingScene::step(){
	if(!isAlive(m_pPlayers[0])){
		return nullptr;
	}

	stepping(m_pEnemies);
	stepping(m_pPlayers);
	stepping(m_pMyBullets);
	stepping(m_pEnemyBullets);
	
	hitCheck(m_pEnemies,m_pMyBullets);
	hitCheck(m_pPlayers,m_pEnemyBullets);
	hitCheck(m_pPlayers,m_pEnemies);

	return this;
}