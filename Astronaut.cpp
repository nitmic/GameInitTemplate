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
	Glas::Vector3f m_RotatePower;
	Glas::Vector3f m_SufferPower;
};

Astronaut::Astronaut(){
	__impl__ = std::make_shared<Impl>();
}

Astronaut::Astronaut(std::shared_ptr<Player> & pModel){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_pModel = pModel;
}

Glas::Quaternion Astronaut::getAttitude(){
	return __impl__->m_Attitude;
}


Glas::Vector3f Astronaut::getPosition(){
	return __impl__->m_Pos;
}

void Astronaut::thrust(
	const std::shared_ptr<JetAgent> & jetL,
	const std::shared_ptr<JetAgent> & jetR,
	const std::shared_ptr<RCSAgent> & jetRCS
){
	__impl__->m_Attitude = jetRCS->getRolling() * __impl__->m_Attitude;
	__impl__->m_Attitude.normalize();

	auto l = jetL->getPropellant();
	auto r = jetR->getPropellant();
	if(l.getLength()+r.getLength()>0){
		if(l.getLength()*r.getLength()>0){
			__impl__->m_RotatePower *= 0.9;
			// どちらも出力あり
			Glas::Vector3f power = jetL->getPropellant() + jetR->getPropellant();
			__impl__->m_SufferPower += power;
			__impl__->m_RotatePower *= 0.97;
			if(__impl__->m_SufferPower.getLength()>3){
				__impl__->m_SufferPower.normalize();
				__impl__->m_SufferPower *= 3;
			}
			return;
		}
		// どちらかのみが出力あり
		l.X = 0;
		r.X = 0;
		__impl__->m_RotatePower += l-r;
		return;
	}
	__impl__->m_RotatePower *= 0.9;
	__impl__->m_SufferPower *= 0.9;
}

bool Astronaut::isAlive(){
	return !(getAir().isEmpty() || getLife().isEmpty());
}

void Astronaut::step(){
	// パワーを回転 移動エネルギーに
	{
		Glas::Quaternion q;

		Glas::Vector3f defaultL(-1,0,0);
		auto rotated = defaultL+__impl__->m_RotatePower;
		q.rotationFromTo(defaultL, rotated.normalize());

		__impl__->m_Attitude = q * __impl__->m_Attitude;
		__impl__->m_Attitude.normalize();
	}
	__impl__->m_Pos += __impl__->m_Attitude * __impl__->m_SufferPower;

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