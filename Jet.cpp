#include "Jet.h"
#include "ParticleIrrAdapter.h"

///////////////////         Jet         /////////////////////////////


/*
*@class JetAgent
*/

struct JetAgent::Impl{
	Impl(){}

	std::shared_ptr<I3DAgent> m_Agent;
	Glas::Vector3f m_Offset;

	Glas::Vector3f direction;
};

JetAgent::JetAgent(){
	__impl__ = std::make_shared<Impl>();
};

bool JetAgent::isAlive(){
	return __impl__->direction.getLength()>0;
}

void JetAgent::thrust(Glas::Vector3f direction){
	__impl__->direction = direction;
}

void JetAgent::Join(
	std::shared_ptr<I3DAgent> agent,
	Glas::Vector3f offset
){
	__impl__->m_Agent = agent;
	__impl__->m_Offset = offset;
}

Glas::Quaternion JetAgent::getAttitude(){
	Glas::Quaternion q;
	Glas::Vector3f from(0,1,0);
	Glas::Vector3f to =  -1 * __impl__->direction;
	q.rotationFromTo(from, __impl__->m_Agent->getAttitude() * to);
	q.normalize();
	return q;
}

Glas::Vector3f JetAgent::getPropellant(){
	return __impl__->direction;
}

Glas::Vector3f JetAgent::getPosition(){
	return (
		__impl__->m_Agent->getPosition()
		 + __impl__->m_Agent->getAttitude()
		 * __impl__->m_Offset
	);
}


/*
*@class JetDrawer
*/

struct JetDrawer::Impl{
	ParticleSystem m_Jet;
	std::shared_ptr<JetAgent> m_pAgent;
};

JetDrawer::JetDrawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_Jet.stop();
}

JetDrawer::JetDrawer(std::shared_ptr<JetAgent> & agent){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_pAgent = agent;
	__impl__->m_Jet.stop();
}

void JetDrawer::draw(){
	__impl__->m_Jet.setPosition(__impl__->m_pAgent->getPosition());
	__impl__->m_Jet.setAttitude(__impl__->m_pAgent->getAttitude());
	__impl__->m_Jet.draw();
	if(__impl__->m_pAgent->isAlive()){
		__impl__->m_Jet.start();
	}else{
		__impl__->m_Jet.stop();
	}
}

bool JetDrawer::isVisible(){
	return true;
}

/////////////////////      RCS        ///////////////////////////


/*
*@class RCSAgent
*/

struct RCSAgent::Impl{
	std::shared_ptr<I3DAgent> m_Agent;
	Glas::Vector3f m_Offset;
	
	Glas::Vector3f direction;
	Glas::Quaternion rolling;
};

RCSAgent::RCSAgent(){
	__impl__ = std::make_shared<Impl>();
};
void RCSAgent::step(){
	
};

bool RCSAgent::isAlive(){
	return __impl__->direction.getLength()>0;
};

void RCSAgent::Join(
	std::shared_ptr<I3DAgent> agent,
	Glas::Vector3f offset
){
	__impl__->m_Agent = agent;
	__impl__->m_Offset = offset;
}

void RCSAgent::rolling(Glas::Vector3f direction){
	// 0‚È‚çŒ»Ý‚Ì‘¬“x‚ð‹}‘¬‚É—Ž‚Æ‚·
	__impl__->direction = direction.getLength()==0 ? __impl__->direction*0.9 : direction;
	
	Glas::Vector3f defaultL(0, 1, 0);
	auto rotated = defaultL+__impl__->direction;
	__impl__->rolling.rotationFromTo(defaultL, rotated.normalize());
}

Glas::Quaternion RCSAgent::getRolling(){

	return __impl__->rolling;
}

Glas::Quaternion RCSAgent::getAttitude(){
	return __impl__->m_Agent->getAttitude();
}
Glas::Vector3f RCSAgent::getPosition(){
	return __impl__->m_Agent->getPosition();
}


/*
*@class RCSDrawer
*/

struct RCSDrawer::Impl{
	ParticleSystem m_Jet;
	std::shared_ptr<RCSAgent> m_pAgent;
};

RCSDrawer::RCSDrawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_Jet.stop();
}

RCSDrawer::RCSDrawer(std::shared_ptr<RCSAgent> & agent){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_pAgent = agent;
	__impl__->m_Jet.stop();
}

void RCSDrawer::draw(){
}

bool RCSDrawer::isVisible(){
	return true;
}