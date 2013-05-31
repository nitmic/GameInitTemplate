#include "Scene.h"
#include "MDAUtility.hpp"
#include "HitCheck.hpp"
#include <algorithm>

void ShootingScene::draw(){
	drawing(m_pDrawers);
}

NextScene ShootingScene::step(){
	if(!all_of(m_pPlayers.begin(), m_pPlayers.end(), isAlive<remove_pointer<Player>::type>)){
		return nullptr;
	}

	stepping(m_pEnemies);
	stepping(m_pPlayers);
	stepping(m_pMyBullets);
	stepping(m_pEnemyBullets);
	
	hitCheck(m_pEnemies, m_pMyBullets);
	hitCheck(m_pPlayers, m_pEnemyBullets);
	hitCheck(m_pPlayers, m_pEnemies);

	return this;
}