#include "Astronaut.h"
#include "Player.h"
#include "3DObjectIrrAdapter.h"
#include "Jet.h"


/*
*@class Astronaut
*/

struct Astronaut::Impl{
	Impl()  : m_Attitude(0,0,0){};

	Air m_air;
	Life m_life;
	Glas::Vector3f m_Pos;
	Glas::Quaternion m_Attitude;
	std::shared_ptr<Player> m_pModel;
};

Glas::Quaternion Astronaut::getAttitude(){
	return __impl__->m_Attitude;
};


Glas::Vector3f Astronaut::getPosition(){
	return __impl__->m_Pos;
}

void Astronaut::thrust(
	const std::shared_ptr<JetAgent> & jetL,
	const std::shared_ptr<JetAgent> & jetR
){
	{
		auto l = jetL->getPropellant();
		l.X = 0;
		auto r = jetR->getPropellant();
		r.X = 0;
		m_RotatePower += l-r;
	}
	{
		Glas::Vector3f power = jetL->getPropellant() + jetR->getPropellant();
		m_SufferPower += m_Attitude * power;
	}
}

bool Astronaut::isAlive(){
	return !(getAir().isEmpty() || getLife().isEmpty());
}

void Astronaut::step(){
	// 制動装置
	std::for_each(m_RotatePower.begin(), m_RotatePower.end(), [&](float & f){
		if(f<-0.0001) f += 0.0001;
		if(f>0.0001) f -= 0.0001;
	});
	std::for_each(m_SufferPower.begin(), m_SufferPower.end(), [&](float & f){
		if(f<-0.0001) f += 0.0001;
		if(f>0.0001) f -= 0.0001;
	});
	// パワーを回転 移動エネルギーに
	{
		Glas::Quaternion q;

		Glas::Vector3f defaultL(-1,0,0);
		auto rotated = defaultL+m_RotatePower;
		q.rotationFromTo(defaultL, rotated.normalize());

		m_Attitude = q * m_Attitude;
		m_Attitude.normalize();
	}
	m_Pos += m_SufferPower;

}

Air Astronaut::getAir(){ return __impl__->m_air;};
Life Astronaut::getLife(){ return __impl__->m_life;}



/*
*@class AstronautDrawer
*/

struct AstronautDrawer::Impl{
	Drawer3DImpl m_drawer;
	std::shared_ptr<Astronaut> m_pAgent;
};

AstronautDrawer::AstronautDrawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setResouceName(_T("./space/astronauts.x"));
}

AstronautDrawer::AstronautDrawer(std::shared_ptr<Astronaut> agent){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setResouceName(_T("./space/astronauts.x"));
	__impl__->m_pAgent = agent;
}

bool AstronautDrawer::isVisible(){
	return true;
}

void AstronautDrawer::draw(){
	__impl__->m_drawer.setPosition(__impl__->m_pAgent->getPosition());
	__impl__->m_drawer.setAttitude(__impl__->m_pAgent->getAttitude());
	__impl__->m_drawer.draw();
}



////////////////////////      other       ///////////////////////


bool Air::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Life::isEmpty(){
	return Percent(0) >= m_rest;
}