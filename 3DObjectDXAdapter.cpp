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
void DXAdapter::Drawer3DImpl::setPosition(Glas::Vector3f pos){
	m_Pos = pos;
}
void DXAdapter::Drawer3DImpl::setScale(float amount){
	m_Scale[0] = amount;
	m_Scale[1] = amount;
	m_Scale[2] = amount;
}