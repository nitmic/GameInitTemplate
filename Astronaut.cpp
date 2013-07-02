#include "Astronaut.h"
#include "Player.h"
#include "3DObjectDXAdapter.h"

using namespace DXAdapter;

struct AstronautDrawer::Impl{
	Drawer3DImpl m_drawer;
	std::shared_ptr<Player> m_pModel;
};

AstronautDrawer::AstronautDrawer(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setResouceName(_T("./space/astronauts.x"));
}

AstronautDrawer::AstronautDrawer(std::shared_ptr<Player> model){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_drawer.setResouceName(_T("./space/astronauts.x"));
	__impl__->m_pModel = model;
}

bool AstronautDrawer::isVisible(){
	return true;
}

void AstronautDrawer::draw(){
	__impl__->m_drawer.setPosition(__impl__->m_pModel->getPosition());
	__impl__->m_drawer.draw();
}

bool Astronaut::isAlive(){
	return !(m_pModel->getAir().isEmpty() || m_pModel->getLife().isEmpty());
}
void Astronaut::step(){

}