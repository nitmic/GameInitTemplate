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

	//�C���X�^���X�̐���
	auto pApp = GetSingleton<DXApp>();
	auto pWindow = GetSingleton<DXWindow>();
	//�Z�b�g�A�b�v
	if(pApp->Setup(hInstance, 800, 600, true) == false){
		return 0;
	}

	pApp->setOnFrameDraw([&]{
	});
	pApp->setOnFrameUpdate([&]()->bool{
		return true;
	});

	pWindow->setProc(&WindowProc);

	//�E�B���h�E�̕\��
	ShowWindow(pWindow->getHWND(), nCmdShow);


	//���C�����[�v
	pApp->AppLoop();


	return 0;
}