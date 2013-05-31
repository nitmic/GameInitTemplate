#pragma once
#include "MDAUtility.hpp"
#include "ShootingObject.h"

template<class Agent, class Bullet>
bool isCollision(Agent & agent, Bullet & bullet){
	return false;
}


template<class Agent, class Bullet>
void hitCheck(Agent & agent, Bullet & bullet){
	if(!isAlive(agent) || !isAlive(bullet)) return;
	auto & shared_agent = getShared(agent);
	auto & shared_bullet = getShared(bullet);
	if(isCollision(shared_agent, shared_bullet)){
		shared_agent->hit(shared_bullet.get());
		shared_bullet->shot(shared_agent.get());
	}
}

template<class Agent, class Bullet>
void hitCheck(Agent & agent, std::vector<Bullet> & bullets){
	if(!isAlive(agent)) return;
	auto & shared_agent = getShared(agent);
	isAliveOrErase(bullets,[&](typename toShared<Bullet>::type & bullet){
		hitCheck(shared_agent, bullet);
	});
}

template<class Agent, class Bullet>
void hitCheck(std::vector<Agent> & agents, std::vector<Bullet> & bullets){
	isAliveOrErase(agents,[&](typename toShared<Agent>::type & agent){
		hitCheck(agent, bullets);
	});
}