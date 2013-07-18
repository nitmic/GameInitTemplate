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
	auto l = jetL.direction*jetL.power;
	l.X = 0;
	auto r = jetR.direction*jetR.power;
	r.X = 0;
	
	m_RotatePower += l - r;


	
}
bool Astronaut::isAlive(){
	return !(getAir().isEmpty() || getLife().isEmpty());
}
void Astronaut::step(){
	Glas::Quaternion q;

	Glas::Vector3f defaultL(-1,0,0);
	auto rotated = defaultL+m_RotatePower;
	q.rotationFromTo(defaultL, rotated.normalize());

	m_Attitude = q * m_Attitude;
	m_Attitude.normalize();

	/*
	TUL::Radian rad(0);
	Glas::Vector3f axis;
	m_Attitude.toAngleAxis(rad, axis);
	
	toStringStream ostr;
	ostr << _T("key: ") << rad.getRaw() << _T(", ") << axis.X << _T(", ") << axis.Y << _T(", ") << axis.Z << _T(", ") ;
	Debug(ostr.str());
	*/
}




bool Air::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Life::isEmpty(){
	return Percent(0) >= m_rest;
}