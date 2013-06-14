#include <DXLib3D.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
   if(mes == WM_DESTROY) {PostQuitMessage(0); return 0;}
   return DefWindowProc(hWnd, mes, wParam, lParam);
}

bool CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM w, LPARAM l){
	GetSingleton<DXLib::DXEditCamera>()->EditCameraProc(hWnd,msg,w,l);
	return false;
}

int APIENTRY _tWinMain(
					   HINSTANCE hInstance, 
					   HINSTANCE hPrevInstance, 
					   LPTSTR	 lpCmdLine,
					   int		 nCmdShow)
{

	//�C���X�^���X�̐���
	auto pApp = GetSingleton<DXLib::DXApp>();
	auto pWindow = GetSingleton<DXLib::DXWindow>();
	//�Z�b�g�A�b�v
	if(pApp->Setup(hInstance, 800, 600, true) == false){
		return 0;
	}
	D3DXMATRIXA16    matWorld;      //���[���h�s��
	D3DXMATRIXA16    matPosition;   //�ړ��s��
	D3DXMatrixIdentity(&matWorld);  //������

	//�ړ��s����쐬
	D3DXMatrixTranslation(
		&matPosition,
		0,  //X���W
		0,  //Y���W
		-10   //Z���W
	);
	matWorld *= matPosition;
	
	DXLib::DXMesh pencil;
	if(FAILED(pencil.load(_T("house.x")))){
		ERROR_MSG(_T("house.x �擾�Ɏ��s"));
		return 0;
	}


	pApp->setOnFrameDraw([&]{
		GetSingleton<DXLib::DXEditCamera>()->transform();
		pencil.draw(matWorld);
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