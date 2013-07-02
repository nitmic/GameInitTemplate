#pragma once
#include <algorithm>
#include "3DObjectDXAdapter.h"
using namespace DXAdapter;

#include "MDA.h"

class Stage : public IDrawer{
public:
	Stage(){
		m_drawer.setResouceName(_T("./space/background.x"));
		Blas::Vector3f v;
		std::fill(v.begin(),v.end(), 0);
		m_drawer.setPosition(v);
		m_drawer.setScale(30);
	}
	bool isVisible(){return true;};
	void draw(){
		m_drawer.draw();
	};
	void setPosition(Blas::Vector3f v){
		m_drawer.setPosition(v);
	}
private:
	Drawer3DImpl m_drawer;
};