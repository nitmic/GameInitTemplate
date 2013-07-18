#include "GameScene.h"
#include "MDAUtility.hpp"

#include "SceneHandler.h"
#include "IDebris.h"
#include "Player.h"
#include "Astronaut.h"
#include "Camera.h"
#include "Stage.h"

#include "JoypadDXAdapter.h"
#include "lightIrrAdapter.h"
#include "CameraIrrAdapter.hpp"


struct GameScene::Impl{
	Impl() : joypad(0){}
	std::shared_ptr<Player> m_pPlayer; // model
	std::shared_ptr<Astronaut> m_pAstronaut; // agent
	std::shared_ptr<Astronaut> m_pAstro;
	Camera<TPSCamera> m_Camera;

	typedef std::shared_ptr<IDebri> Debri;
	typedef std::vector<Debri> Debris;
	Debris m_pDebris; // model + agent

	typedef std::shared_ptr<IDrawer> Drawer;
	typedef std::vector<Drawer> Drawers;
	Drawers m_pDrawers;

	std::shared_ptr<Stage> m_pStage;
	

	Joypad joypad;
};

GameScene::GameScene(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_pPlayer = std::make_shared<Player>();
	__impl__->m_pAstronaut = std::make_shared<Astronaut>();
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(__impl__->m_pAstronaut));

	auto deb = std::make_shared<Astronaut>();
	__impl__->m_pAstro = deb;
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(deb));

	__impl__->m_pStage = std::make_shared<Stage>();
	__impl__->m_pDrawers.push_back(__impl__->m_pStage);
	
	__impl__->m_Camera.setTarget(__impl__->m_pAstronaut);
}

void GameScene::draw(){
	__impl__->m_Camera.transform();
	drawing(__impl__->m_pDrawers);
}

void GameScene::step(
	SceneHandler * sceneHandler
){
	auto & j = __impl__->joypad;
	j.update();
	{
		auto jLTilt = j.getLStick().getTilt();//.normalize(); // ŽÀ‘•ŠÔˆá‚Á‚Ä‚é‚©‚à
		JetPower jetL;
		jetL.direction.X = jLTilt.X;
		auto length = jLTilt.getLength();
		jetL.direction.Y = 1 - length;
		jetL.direction.Z = -jLTilt.Y;
		jetL.power = j.getButton(AbsJoypad::L1).isPressed() ? 0.001 : 0;

		auto jRTilt = j.getRStick().getTilt();
		JetPower jetR;
		jetR.direction.X = jRTilt.X;
		jetR.direction.Y = 1 - jRTilt.getLength();
		jetR.direction.Z = -jRTilt.Y;
		jetR.power = j.getButton(AbsJoypad::R1).isPressed() ? 0.001 : 0;

		__impl__->m_pAstronaut->jetPropellant(jetL, jetR);
	}
	__impl__->m_pAstronaut->step();
	////////////////////////

	if(j.getButton(AbsJoypad::L2).isPressed() && j.getButton(AbsJoypad::R2).isPressed()){
		__impl__->m_Camera.normalize();
	}
	if(j.getButton(AbsJoypad::L2).isPressed() && !(j.getButton(AbsJoypad::R2).isPressed())){
		__impl__->m_Camera.rotate(3);
	}
	if(j.getButton(AbsJoypad::R2).isPressed() && !(j.getButton(AbsJoypad::L2).isPressed())){
		__impl__->m_Camera.rotate(-3);
	}

	/////////////////////
	
	if(j.getButton(AbsJoypad::A).isPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() * 1.05);
	}
	if(j.getButton(AbsJoypad::B).isPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() / 1.05);
	}

	////////////////////
	
	__impl__->m_pStage->setPosition(__impl__->m_pAstronaut->getPosition());

	sceneHandler->setNextScene(sceneHandler->getCurrentScene());
}