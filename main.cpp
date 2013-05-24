#include <DXLibCore.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
   if(mes == WM_DESTROY) {PostQuitMessage(0); return 0;}
   return DefWindowProc(hWnd, mes, wParam, lParam);
}

bool CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM w, LPARAM l)
{
	return false;
}

int APIENTRY _tWinMain(
					   HINSTANCE hInstance, 
					   HINSTANCE hPrevInstance, 
					   LPTSTR	 lpCmdLine,
					   int		 nCmdShow)
{

	//インスタンスの生成
	auto pApp = GetSingleton<DXApp>();
	auto pWindow = GetSingleton<DXWindow>();
	//セットアップ
	if(pApp->Setup(hInstance, 800, 600, true) == false){
		return 0;
	}

	pApp->setOnFrameDraw([&]{
	});
	pApp->setOnFrameUpdate([&]()->bool{
		return true;
	});

	pWindow->setProc(&WindowProc);

	//ウィンドウの表示
	ShowWindow(pWindow->getHWND(), nCmdShow);


	//メインループ
	pApp->AppLoop();


	return 0;
}