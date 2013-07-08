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
	Camera<TPSCamera> m_Camera;

	typedef std::shared_ptr<IDebri> Debri;
	typedef std::vector<Debri> Debris;
	Debris m_pDebris; // model + agent

	typedef std::shared_ptr<IDrawer> Drawer;
	typedef std::vector<Drawer> Drawers;
	Drawers m_pDrawers;

	std::shared_ptr<Stage> m_pStage;
	
	Light light;

	Joypad joypad;
};

GameScene::GameScene(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_pPlayer = std::make_shared<Player>();
	__impl__->m_pAstronaut = std::make_shared<Astronaut>();
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(__impl__->m_pAstronaut));

	__impl__->m_pStage = std::make_shared<Stage>();
	__impl__->m_pDrawers.push_back(__impl__->m_pStage);
	
	__impl__->m_Camera.setTarget(__impl__->m_pAstronaut);
}

void GameScene::draw(){
	__impl__->light.draw();
	__impl__->m_Camera.transform();
	drawing(__impl__->m_pDrawers);
}

void GameScene::step(
	SceneHandler * sceneHandler
){
	/*auto & j = __impl__->joypad;
	j.update();

	auto & jLTilt = j.getLStick().getTilt();
	JetPower jetL;
	jetL.direction = jLTilt.normalize();
	jetL.power = 0;

	auto & jRTilt = j.getRStick().getTilt();
	JetPower jetR;
	jetR.direction = jRTilt.normalize();
	jetR.power = 0;

	if(j.getButton(AbsJoypad::L1).isPressed()){
		jetL.power = jLTilt.getLength();
	}else{
		std::fill(jetL.direction.begin(), jetL.direction.end(), 0);
	}
	if(j.getButton(AbsJoypad::R1).isPressed()){
		jetR.power = jRTilt.getLength();
	}else{
		std::fill(jetR.direction.begin(), jetR.direction.end(), 0);
	}
	__impl__->m_pPlayer->jetPropellant(jetL, jetR);
	
	////////////////////////

	if(j.getButton(AbsJoypad::L2).isPressed() && j.getButton(AbsJoypad::R2).isPressed()){
		//__impl__->m_Camera.setVirtical(__impl__->m_pPlayer->getVertical());
		//__impl__->m_Camera.setDirection(__impl__->m_pPlayer->getDirection());
	}
	if(j.getButton(AbsJoypad::L2).isPressed() && !(j.getButton(AbsJoypad::R2).isPressed())){
		__impl__->m_Camera.rotate(1);
	}
	if(j.getButton(AbsJoypad::R2).isPressed() && !(j.getButton(AbsJoypad::L2).isPressed())){
		__impl__->m_Camera.rotate(-1);
	}

	/////////////////////
	
	if(j.getButton(AbsJoypad::A).isJustPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() * 1.5);
	}
	if(j.getButton(AbsJoypad::B).isJustPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() / 1.5);
	}

	////////////////////
	*/
	__impl__->m_pStage->setPosition(__impl__->m_pAstronaut->getPosition());


	sceneHandler->setNextScene(sceneHandler->getCurrentScene());
}