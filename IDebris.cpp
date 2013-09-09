#include "IDebris.h"
#include "3DObjectIrrAdapter.h"

struct Meteor1::Impl{
	Impl()  : m_Attitude(0,0,0), r(5){};
	float r;
	Glas::Vector3f m_Pos;
	Glas::Quaternion m_Attitude;
	Glas::Vector3f m_RotatePower;
	Glas::Vector3f m_SufferPower;
};

Meteor1::Meteor1(){
	__impl__ = std::make_shared<Impl>();
}
Meteor1::Meteor1(Glas::Vector3f pos, Glas::Vector3f rotate, Glas::Vector3f velocity){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_Pos = pos;
	__impl__->m_RotatePower = rotate;
	__impl__->m_SufferPower = velocity;
}

Glas::Quaternion Meteor1::getAttitude(){
	return __impl__->m_Attitude;
}


Glas::Vector3f Meteor1::getPosition(){
	return __impl__->m_Pos;
}

void Meteor1::step(){
	// パワーを回転 移動エネルギーに
	{
		Glas::Quaternion q;

		Glas::Vector3f defaultL(-1,0,0);
		auto rotated = defaultL+__impl__->m_RotatePower;
		q.rotationFromTo(defaultL, rotated.normalize());

		__impl__->m_Attitude = q * __impl__->m_Attitude;
		__impl__->m_Attitude.normalize();
	}
	__impl__->m_Pos += __impl__->m_SufferPower;

}







/*
*@class Meteor1Drawer
*/

struct Meteor1Drawer::Impl{
	Drawer3DImpl m_drawer;
	std::shared_ptr<Meteor1> m_pAgent;
};

Meteor1Drawer::Meteor1Drawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setScale(2);
	__impl__->m_drawer.setResouceName(_T("./space/deburi1.x"));
}

Meteor1Drawer::Meteor1Drawer(std::shared_ptr<Meteor1> agent){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setScale(2);
	__impl__->m_drawer.setResouceName(_T("./space/deburi1.x"));
	__impl__->m_pAgent = agent;
}

bool Meteor1Drawer::isVisible(){
	return true;
}

void Meteor1Drawer::draw(){
	__impl__->m_drawer.setPosition(__impl__->m_pAgent->getPosition());
	__impl__->m_drawer.setAttitude(__impl__->m_pAgent->getAttitude());
	__impl__->m_drawer.draw();
}








struct Meteor2::Impl{
	Impl()  : m_Attitude(0,0,0), r(5){};
	float r;
	Glas::Vector3f m_Pos;
	Glas::Quaternion m_Attitude;
	Glas::Vector3f m_RotatePower;
	Glas::Vector3f m_SufferPower;
};

Meteor2::Meteor2(){
	__impl__ = std::make_shared<Impl>();
}
Meteor2::Meteor2(Glas::Vector3f pos, Glas::Vector3f rotate, Glas::Vector3f velocity){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_Pos = pos;
	__impl__->m_RotatePower = rotate;
	__impl__->m_SufferPower = velocity;
}

Glas::Quaternion Meteor2::getAttitude(){
	return __impl__->m_Attitude;
}


Glas::Vector3f Meteor2::getPosition(){
	return __impl__->m_Pos;
}

void Meteor2::step(){
	// パワーを回転 移動エネルギーに
	{
		Glas::Quaternion q;

		Glas::Vector3f defaultL(-1,0,0);
		auto rotated = defaultL+__impl__->m_RotatePower;
		q.rotationFromTo(defaultL, rotated.normalize());

		__impl__->m_Attitude = q * __impl__->m_Attitude;
		__impl__->m_Attitude.normalize();
	}
	__impl__->m_Pos += __impl__->m_SufferPower;

}







/*
*@class Meteor1Drawer
*/

struct Meteor2Drawer::Impl{
	Drawer3DImpl m_drawer;
	std::shared_ptr<Meteor2> m_pAgent;
};

Meteor2Drawer::Meteor2Drawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setScale(4);
	__impl__->m_drawer.setResouceName(_T("./space/deburi4.x"));
}

Meteor2Drawer::Meteor2Drawer(std::shared_ptr<Meteor2> agent){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setScale(4);
	__impl__->m_drawer.setResouceName(_T("./space/deburi4.x"));
	__impl__->m_pAgent = agent;
}

bool Meteor2Drawer::isVisible(){
	return true;
}

void Meteor2Drawer::draw(){
	__impl__->m_drawer.setPosition(__impl__->m_pAgent->getPosition());
	__impl__->m_drawer.setAttitude(__impl__->m_pAgent->getAttitude());
	__impl__->m_drawer.draw();
}
