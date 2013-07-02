#include "DXAdapter.h"
#include "GameScene.h"
#include <DX3DRendering.h>
#include <DXRenderingEngineStorage.h>
#include <DXDeviceObject.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
   if(mes == WM_DESTROY) {PostQuitMessage(0); return 0;}
   return DefWindowProc(hWnd, mes, wParam, lParam);
}

bool CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM w, LPARAM l){
	//GetSingleton<DXLib::DXEditCamera>()->EditCameraProc(hWnd,msg,w,l);
	return false;
}

int APIENTRY _tWinMain(
					   HINSTANCE hInstance, 
					   HINSTANCE hPrevInstance, 
					   LPTSTR	 lpCmdLine,
					   int		 nCmdShow
){
	
	DXLib::DXDeviceObject::getPathStorage().regist(_T("./space"));
	//�Z�b�g�A�b�v
	auto pApp = DXLib::DXInitialize<DXLib::DX3DRendering>(hInstance, 800, 600, true);
	if(!pApp){
		return 0;
	}
	auto pWindow = GetSingleton<DXLib::DXWindow>();


	auto startScene = std::make_shared<GameScene>();
	GameLoop gameLoop(startScene);

	pApp->setOnFrameDraw([&]{
		gameLoop.draw();
	});

	pApp->setOnFrameUpdate([&]()->bool{
		return gameLoop.update();
	});
	
	pWindow->setProc(&WindowProc);

	//�E�B���h�E�̕\��
	ShowWindow(pWindow->getHWND(), nCmdShow);


	//���C�����[�v
	pApp->AppLoop();


	return 0;
}