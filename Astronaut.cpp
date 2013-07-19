#include "Astronaut.h"
#include "Player.h"
#include "3DObjectIrrAdapter.h"
#include "Debug.h"

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



Glas::Vector3f Astronaut::getPosition(){
	return m_Pos;
}

void Astronaut::jetPropellant(JetPower jetL, JetPower jetR){
	{
		auto l = jetL.direction*jetL.power;
		l.X = 0;
		auto r = jetR.direction*jetR.power;
		r.X = 0;
		m_RotatePower += l - r;
	}
	{
		auto l = jetL.direction*jetL.power*5;
		auto r = jetR.direction*jetR.power*5;
		m_SufferPower += l+r;
	}
}
bool Astronaut::isAlive(){
	return !(getAir().isEmpty() || getLife().isEmpty());
}
void Astronaut::step(){
	// 制動装置
	std::for_each(m_RotatePower.begin(), m_RotatePower.end(), [&](float & f){
		if(f<-0.0001) f += 0.00003;
		if(f>0.0001) f -= 0.00003;
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
	m_Pos += m_Attitude * m_SufferPower;

}




bool Air::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Life::isEmpty(){
	return Percent(0) >= m_rest;
}