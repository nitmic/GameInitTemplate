#include "GameScene.h"
#include "MDAUtility.hpp"

#include "SceneHandler.h"
#include "IDebris.h"
#include "Player.h"
#include "Astronaut.h"
#include "Jet.h"
#include "Camera.h"
#include "Stage.h"

#include "JoypadDXAdapter.h"
#include "lightIrrAdapter.h"
#include "CameraIrrAdapter.hpp"

struct GameScene::Impl{
	Impl() : joypad(0){}
	std::shared_ptr<Player> m_pPlayer; // model
	std::shared_ptr<Astronaut> m_pAstronaut; // agent
	std::shared_ptr<JetAgent> m_pJetL;
	std::shared_ptr<JetAgent> m_pJetR;
	std::shared_ptr<RCSAgent> m_pRCS;

	//std::shared_ptr<Astronaut> m_pAstro;

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
	
	
	__impl__->m_pJetL = std::make_shared<JetAgent>();
	__impl__->m_pJetL->Join(__impl__->m_pAstronaut, Glas::Vector3f(-0.5,-0.3f,0));
	__impl__->m_pDrawers.push_back(std::make_shared<JetDrawer>(__impl__->m_pJetL));
	__impl__->m_pJetR = std::make_shared<JetAgent>();
	__impl__->m_pJetR->Join(__impl__->m_pAstronaut, Glas::Vector3f(0.5,-0.3f,0));
	__impl__->m_pDrawers.push_back(std::make_shared<JetDrawer>(__impl__->m_pJetR));
	__impl__->m_pRCS = std::make_shared<RCSAgent>();
	__impl__->m_pRCS->Join(__impl__->m_pAstronaut);
	__impl__->m_pDrawers.push_back(std::make_shared<RCSDrawer>(__impl__->m_pRCS));
	/*
	auto deb = std::make_shared<Astronaut>();
	__impl__->m_pAstro = deb;
	__impl__->m_pDrawers.push_back(std::make_shared<AstronautDrawer>(deb));
	*/
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
		if(j.getButton(AbsJoypad::L1).isPressed()){
			Glas::Vector3f direction(0, 0, 0.001);
			__impl__->m_pJetL->thrust(direction);
		}
		if(j.getButton(AbsJoypad::R1).isPressed()){
			Glas::Vector3f direction(0, 0, 0.001);
			__impl__->m_pJetL->thrust(direction);
		}
		__impl__->m_pAstronaut->thrust(
			__impl__->m_pJetL, __impl__->m_pJetR
		);
	}

	///////

	{
		Glas::Vector3f direction;
		if(j.getButton(AbsJoypad::Left).isPressed()){
			direction.X = -1;
		}
		if(j.getButton(AbsJoypad::Right).isPressed()){
			direction.X = 1;
		}
		if(j.getButton(AbsJoypad::Down).isPressed()){
			direction.Y = -1;
		}
		if(j.getButton(AbsJoypad::Up).isPressed()){
			direction.Y = 1;
		}
		__impl__->m_pRCS->rolling(direction);
	}

	__impl__->m_pAstronaut->step();


	////////////////////////
	/*
	if(j.getButton(AbsJoypad::L2).isPressed() && j.getButton(AbsJoypad::R2).isPressed()){
		__impl__->m_Camera.normalize();
	}
	if(j.getButton(AbsJoypad::L2).isPressed() && !(j.getButton(AbsJoypad::R2).isPressed())){
		__impl__->m_Camera.rotate(3);
	}
	if(j.getButton(AbsJoypad::R2).isPressed() && !(j.getButton(AbsJoypad::L2).isPressed())){
		__impl__->m_Camera.rotate(-3);
	}*/

	/////////////////////
	/*
	if(j.getButton(AbsJoypad::A).isPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() * 1.05);
	}
	if(j.getButton(AbsJoypad::B).isPressed()){
		__impl__->m_Camera.setDistance(__impl__->m_Camera.getDistance() / 1.05);
	}*/

	////////////////////
	
	__impl__->m_pStage->setPosition(__impl__->m_pAstronaut->getPosition());

	sceneHandler->setNextScene(sceneHandler->getCurrentScene());
}