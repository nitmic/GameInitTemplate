#include "3DObjectDXAdapter.h"
#include <DXMeshStorage.h>


void DXAdapter::Drawer3DImpl::draw(){
	D3DXMATRIXA16    matWorld;      //ワールド行列
	D3DXMATRIXA16    matPosition;   //移動行列
	D3DXMATRIXA16    matRotationX;   //回転行列
	D3DXMATRIXA16    matRotationY;   //回転行列
	D3DXMATRIXA16    matRotationZ;   //回転行列
	D3DXMATRIXA16    matScale;   //拡大縮小

	D3DXMatrixIdentity(&matWorld);  //初期化

	///////////////////

	Blas::Vector3f virticalY;
	virticalY[0] = 0;
	virticalY[1] = 1;
	virticalY[2] = 0;
	float yRad = Blas::angle(m_Virtical, virticalY);

	D3DXMatrixRotationY(
		&matRotationY,
		yRad
	);
	//matWorld *= matRotationY;
	
	/////////////////////

	Blas::Vector3f virticalX;
	virticalX[0] = 1;
	virticalX[1] = 0;
	virticalX[2] = 0;
	float xRad = Blas::angle(m_Virtical, virticalX);


	D3DXMatrixRotationX(
		&matRotationX,
		xRad
	);
	//matWorld *= matRotationX;

	///////////////////

	Blas::Vector3f virticalZ;
	virticalZ[0] = 0;
	virticalZ[1] = 0;
	virticalZ[2] = 1;
	float zRad = Blas::angle(m_Virtical, virticalZ);

	D3DXMatrixRotationZ(
		&matRotationZ,
		zRad
	);
	//matWorld *= matRotationZ;

	//////////////////
	D3DXMatrixScaling(
		&matScale,
		m_Scale[0],
		m_Scale[1],
		m_Scale[2]
	);
	matWorld *= matScale;

	//移動行列を作成
	D3DXMatrixTranslation(
		&matPosition,
		m_Pos[0],
		m_Pos[1],
		m_Pos[2]
	);
	matWorld *= matPosition;

	
	GetSingleton<DXLib::DXMeshStorage>()->find(m_name)->draw(matWorld);
};

void DXAdapter::Drawer3DImpl::setResouceName(tString name){
	m_name = name;
}
void DXAdapter::Drawer3DImpl::setPosition(Blas::Vector3f pos){
	m_Pos = pos;
}
void DXAdapter::Drawer3DImpl::setDirection(Blas::Vector3f direction){
	m_Direction = direction;
}
void DXAdapter::Drawer3DImpl::setVirtical(Blas::Vector3f virtical){
	m_Virtical = virtical;
}
void DXAdapter::Drawer3DImpl::setScale(float amount){
	m_Scale[0] = amount;
	m_Scale[1] = amount;
	m_Scale[2] = amount;
}