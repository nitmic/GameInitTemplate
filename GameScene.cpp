#include "GameScene.h"
#include "MDAUtility.hpp"

#include "SceneHandler.h"
#include "IDebris.h"
#include "Player.h"
#include "Astronaut.h"
#include "Camera.h"
#include "Stage.h"

#include "CameraDXAdapter.hpp"
#include "JoypadDXAdapter.h"
#include "lightDXAdapter.h"

using namespace DXAdapter;


struct GameScene::Impl{
	Impl() : joypad(0){}
	std::shared_ptr<Player> m_pPlayer; // model
	std::shared_ptr<Player> m_pDebri; // model
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
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(__impl__->m_pPlayer));

	__impl__->m_pDebri = std::make_shared<Player>();
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(__impl__->m_pDebri));

	__impl__->m_pStage = std::make_shared<Stage>();
	__impl__->m_pDrawers.push_back(__impl__->m_pStage);
	
	__impl__->m_Camera.setTarget(__impl__->m_pPlayer);
}

void GameScene::draw(){
	__impl__->light.draw(__impl__->m_Camera.getLookAt() - __impl__->m_Camera.getPosition());
	__impl__->m_Camera.transform();
	drawing(__impl__->m_pDrawers);
}

void GameScene::step(
	SceneHandler * sceneHandler
){
	auto & j = __impl__->joypad;
	j.update();

	auto & jLTilt = j.getLStick().getTilt();
	JetPower jetL;
	jetL.direction = Blas::normalize2(jLTilt);
	jetL.power = 0;

	auto & jRTilt = j.getRStick().getTilt();
	JetPower jetR;
	jetR.direction = Blas::normalize2(jRTilt);
	jetR.power = 0;

	if(j.getButton(AbsJoypad::L1).isPressed()){
		jetL.power = Blas::norm_2(jLTilt);
	}else{
		std::fill(jetL.direction.begin(), jetL.direction.end(), 0);
	}
	if(j.getButton(AbsJoypad::R1).isPressed()){
		jetR.power = Blas::norm_2(jRTilt);
	}else{
		std::fill(jetR.direction.begin(), jetR.direction.end(), 0);
	}
	__impl__->m_pPlayer->jetPropellant(jetL, jetR);
	
	////////////////////////

	if(j.getButton(AbsJoypad::L2).isPressed() && j.getButton(AbsJoypad::R2).isPressed()){
		__impl__->m_Camera.setVirtical(__impl__->m_pPlayer->getVertical());
		__impl__->m_Camera.setDirection(__impl__->m_pPlayer->getDirection());
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

	__impl__->m_pStage->setPosition(__impl__->m_pPlayer->getPosition());


	__impl__->m_Camera.step();
	sceneHandler->setNextScene(sceneHandler->getCurrentScene());
}