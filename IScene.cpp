/*
void ShootingScene::draw(){
	drawing(m_pDrawers);
}

NextScene ShootingScene::step(){
	if(!std::all_of(m_pPlayers.begin(), m_pPlayers.end(), isAliveObject())){
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
}*/
