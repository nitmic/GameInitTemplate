#include "GameScene.h"
#include "MDAUtility.hpp"

#include "SceneHandler.h"
#include "IDebris.h"
#include "Player.h"
#include "Astronaut.h"
#include "Jet.h"
#include "Camera.h"
#include "Stage.h"

#include <stdlib.h>
#include "JoypadDXAdapter.h"
#include "lightIrrAdapter.h"
#include "CameraIrrAdapter.hpp"

struct GameScene::Impl{
public:
	Impl() : joypad(0), frame(0){}
	void thrust();
	void rolling();
	void zoom();
	void createMeteor();
	
	void initPlayer();
private:
	void initJet();
public:
	unsigned long long frame;

	//player
	std::shared_ptr<Player> m_pPlayer; // model
	std::shared_ptr<Astronaut> m_pAstronaut; // agent
	std::shared_ptr<JetAgent> m_pJetL;
	std::shared_ptr<JetAgent> m_pJetR;
	std::shared_ptr<RCSAgent> m_pRCS;

	//camera
	Camera<TPSCamera> m_Camera;

	//debri
	typedef std::shared_ptr<IDebri> Debri;
	typedef std::vector<Debri> Debris;
	Debris m_pDebris; // model + agent

	//drawer
	typedef std::shared_ptr<IDrawer> Drawer;
	typedef std::vector<Drawer> Drawers;
	Drawers m_pDrawers;

	//stage
	std::shared_ptr<Stage> m_pStage;

	//joypad
	Joypad joypad;
};

GameScene::GameScene(){
	__impl__ = std::make_shared<Impl>();

	__impl__->initPlayer();

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
	__impl__->joypad.update();
	
	// 入力によってプレイヤーの移動回転
	__impl__->thrust();
	__impl__->rolling();
	__impl__->m_pAstronaut->thrust(
		__impl__->m_pJetL, __impl__->m_pJetR,
		__impl__->m_pRCS
	);

	// 入力によって画面のズーム
	__impl__->zoom();

	// stepping
	//stepping(__impl__->m_pDebris);
	__impl__->m_pAstronaut->step();
	__impl__->m_Camera.step();

	// 隕石の生成
	//__impl__->createMeteor();

	// カメラを必ずプレイヤーのの後ろに
	__impl__->m_Camera.normalize();

	// ステージはプレイヤーと共に移動
	__impl__->m_pStage->setPosition(__impl__->m_pAstronaut->getPosition());

	// 何も無ければシーン継続
	sceneHandler->setNextScene(sceneHandler->getCurrentScene());
}



//////////////////////////////////////////////////////////////




void GameScene::Impl::thrust(){
	{
		Glas::Vector3f direction(0, 0, 0);
		if(joypad.getButton(AbsJoypad::L1).isPressed()){
			direction.Z = 0.005;
		}
		m_pJetL->thrust(direction);
	}
	{
		Glas::Vector3f direction(0, 0, 0);
		if(joypad.getButton(AbsJoypad::R1).isPressed()){
			direction.Z = 0.005;
		}
		m_pJetR->thrust(direction);
	}

}

void GameScene::Impl::rolling(){
	Glas::Vector3f direction;
	if(joypad.getButton(AbsJoypad::Left).isPressed()){
		direction.X = -0.02;
	}
	if(joypad.getButton(AbsJoypad::Right).isPressed()){
		direction.X = 0.02;
	}
	if(joypad.getButton(AbsJoypad::Down).isPressed()){
		direction.Z = -0.02;
	}
	if(joypad.getButton(AbsJoypad::Up).isPressed()){
		direction.Z = 0.02;
	}
	m_pRCS->rolling(direction);
}

void GameScene::Impl::zoom(){
	if(joypad.getButton(AbsJoypad::A).isPressed()){
		m_Camera.setDistance(m_Camera.getDistance() * 1.05);
	}
	if(joypad.getButton(AbsJoypad::B).isPressed()){
		m_Camera.setDistance(m_Camera.getDistance() / 1.05);
	}
}

void GameScene::Impl::createMeteor(){
	if(frame%60==0){
		for(int max = frame*frame/100000; max>0;max--){
			Glas::Vector3f v(rand()%200-100, rand()%200-100, rand()%200-100);
			auto pos = m_pAstronaut->getPosition() - v;
			v /= rand()%20+100;
			Glas::Vector3f rotate((float)(rand()%10-5)/10, (float)(rand()%10-5)/10, (float)(rand()%10-5)/10);
			if(max%3==0){
				auto meteor = std::make_shared<Meteor1>(pos, rotate, v);
				auto drawer = std::make_shared<Meteor1Drawer>(meteor);
				m_pDebris.push_back(meteor);
				m_pDrawers.push_back(drawer);
			}else if(max%3==1){
				auto meteor = std::make_shared<Meteor2>(pos, rotate, v);
				auto drawer = std::make_shared<Meteor2Drawer>(meteor);
				m_pDebris.push_back(meteor);
				m_pDrawers.push_back(drawer);
			}
		}
	}
	frame++;
}

void GameScene::Impl::initPlayer(){
	m_pPlayer = std::make_shared<Player>();
	m_pAstronaut = std::make_shared<Astronaut>();
	m_pDrawers.push_back(std::make_shared<AstronautDrawer>(m_pAstronaut));
	initJet();
}

void GameScene::Impl::initJet(){		
	m_pJetL = std::make_shared<JetAgent>();
	m_pJetL->Join(m_pAstronaut, Glas::Vector3f(-0.5,-0.3f,0));
	m_pDrawers.push_back(std::make_shared<JetDrawer>(m_pJetL));
	
	m_pJetR = std::make_shared<JetAgent>();
	m_pJetR->Join(m_pAstronaut, Glas::Vector3f(0.5,-0.3f,0));
	m_pDrawers.push_back(std::make_shared<JetDrawer>(m_pJetR));

	m_pRCS = std::make_shared<RCSAgent>();
	m_pRCS->Join(m_pAstronaut);
	m_pDrawers.push_back(std::make_shared<RCSDrawer>(m_pRCS));
}