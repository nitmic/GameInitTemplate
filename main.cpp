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

	//インスタンスの生成
	auto pApp = GetSingleton<DXLib::DXApp>();
	auto pWindow = GetSingleton<DXLib::DXWindow>();
	//セットアップ
	if(pApp->Setup(hInstance, 800, 600, true) == false){
		return 0;
	}
	D3DXMATRIXA16    matWorld;      //ワールド行列
	D3DXMATRIXA16    matPosition;   //移動行列
	D3DXMatrixIdentity(&matWorld);  //初期化

	//移動行列を作成
	D3DXMatrixTranslation(
		&matPosition,
		0,  //X座標
		0,  //Y座標
		-10   //Z座標
	);
	matWorld *= matPosition;
	
	DXLib::DXMesh pencil;
	if(FAILED(pencil.load(_T("house.x")))){
		ERROR_MSG(_T("house.x 取得に失敗"));
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

	//ウィンドウの表示
	ShowWindow(pWindow->getHWND(), nCmdShow);


	//メインループ
	pApp->AppLoop();


	return 0;
}