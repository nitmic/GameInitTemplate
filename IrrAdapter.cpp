#include "IrrAdapter.h"
#include <FPSModerator.h>
#include <tString.h>
#include <memory>
#include <sstream>


struct IrrApp::Impl{
	std::shared_ptr<irr::IrrlichtDevice> device;
	std::function<bool(void)>       m_onFrameUpdate;    //!<	�X�V�p�֐��|�C���^
	std::function<void(void)>       m_onFrameDraw;      //!<	�`��p�֐��|�C���^
};


IrrApp::IrrApp(){
	__impl__ = std::make_shared<Impl>();
	__impl__->m_onFrameUpdate = [](){return true;};
	__impl__->m_onFrameDraw = [](){};
}

void IrrApp::setOnFrameUpdate(std::function<bool(void)> func){
	__impl__->m_onFrameUpdate = func;
}

void IrrApp::setOnFrameDraw(std::function<void(void)> func){
	__impl__->m_onFrameDraw = func;
}

bool IrrApp::Setup(){
	auto device_raw =irr::createDevice(
		irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(800, 600), 32,
		false, true, false, nullptr
	);
	if (!device_raw) return false;
	__impl__->device = std::shared_ptr<irr::IrrlichtDevice>(device_raw, IrrSafeRelease());
	return true;
}

namespace{
	void visibleReset(irr::scene::ISceneNode * node){
		if(!node->isVisible()) return;
		node->setVisible(false);
		for(auto it=node->getChildren().begin();it!=node->getChildren().end();it++){
			visibleReset(*it);
		}
	}
};

void IrrApp::AppLoop(){
	auto fpsModerator = TUL::FPSModerator(60);
	auto lastFPS = -1;
	auto driver = __impl__->device->getVideoDriver();
	auto sm = __impl__->device->getSceneManager();

	while(__impl__->device->run()){
		//�A�N�e�B�u����Ȃ������珈�����Ȃ�
		if(!__impl__->device->isWindowActive()){
			//�r�W�[���[�v��������邽�߂�
			__impl__->device->yield(); 
		}else if(fpsModerator.step()){
			visibleReset(sm->getRootSceneNode());
			sm->getRootSceneNode()->setVisible(true);

			if(!__impl__->m_onFrameUpdate()) break;
			__impl__->m_onFrameDraw();
			driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
			sm->drawAll();
			driver->endScene();
		}else{
			Sleep(1);
		}
		
		auto fps = driver->getFPS();
		if(lastFPS != fps){
			toStringStream ostr;
			ostr << _T("fps: ") << fps;
			__impl__->device->setWindowCaption(ostr.str().c_str());
			lastFPS = fps;
		}
	}
}


irr::IrrlichtDevice * IrrApp::accessDevice(){
	return __impl__->device.get();
}
irr::video::IVideoDriver * IrrApp::accessVideoDriver(){
	return __impl__->device->getVideoDriver();
}
irr::scene::ISceneManager * IrrApp::accessSceneManager(){
	return __impl__->device->getSceneManager();
}