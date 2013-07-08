#include "Astronaut.h"
#include "Player.h"
#include "3DObjectIrrAdapter.h"


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
	__impl__->m_drawer.draw();
}



Glas::Vector3f Astronaut::getPosition(){
	return m_Pos;
}

void Astronaut::jetPropellant(JetPower jetL, JetPower jetR){
	if(jetL.power){
		Glas::Vector2f a = jetL.direction * jetL.power;
		Glas::Vector3f b;
		b[0] = a[0];
		b[1] = a[1];
		b[2] = 0;
		this->m_Pos = this->m_Pos + b;
	}
	if(jetR.power){
		Glas::Vector2f a = jetR.power * jetR.direction;
		Glas::Vector3f b;
		b[0] = a[0];
		b[1] = a[1];
		b[2] = 0;
		this->m_Pos = this->m_Pos + b;
	}
}
bool Astronaut::isAlive(){
	return !(getAir().isEmpty() || getLife().isEmpty());
}
void Astronaut::step(){

}




bool Air::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Life::isEmpty(){
	return Percent(0) >= m_rest;
}