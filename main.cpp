#include "IrrAdapter.h"
#include <FPSModerator.h>
#include "GameScene.h"
#include "GameLoop.h"
#include <Singleton.hpp>
#include <DXManager.h>
#include <DXInput.h>

#include "JoypadDXAdapter.h"

#include "GLAS.h"

#ifdef WIN32
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main()
#endif
{
	auto app = GetSingleton<IrrApp>();
	if(!app->Setup()) return 1;
	auto hWnd = (HWND)app->accessVideoDriver()->getExposedVideoData().D3D9.HWnd;
	
	//Joypad & sound—p
	if(!GetSingleton<DXLib::DXManager>()->Setup(hWnd, 800, 600, true)) return 1;
	if(!GetSingleton<DXLib::DXInput>()->Setup(hInst, hWnd)) return 1;

	auto startScene = std::make_shared<GameScene>();
	GameLoop gameLoop(startScene);
	
	app->setOnFrameUpdate([&]()->bool{
		GetSingleton<DXLib::DXInput>()->Update();
		return gameLoop.update();
	});
	app->setOnFrameDraw([&](){
		gameLoop.draw();
	});

	app->AppLoop();

	return 0;
}