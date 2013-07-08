#pragma once

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>

struct IrrSafeRelease{
	template<class T>
	void operator()(T * p){
		p->drop();
	}
};

#include <Singleton.hpp>

class IrrApp : public Singleton<IrrApp>{
	friend Singleton<IrrApp>;
public:
	IrrApp();
	bool    Setup();
	void	setOnFrameUpdate(std::function<bool(void)> func);
	void	setOnFrameDraw(std::function<void(void)> func);
	void	AppLoop();

	irr::IrrlichtDevice * accessDevice();
	irr::video::IVideoDriver * accessVideoDriver();
	irr::scene::ISceneManager * accessSceneManager();

private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};