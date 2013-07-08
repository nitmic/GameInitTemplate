#pragma once
#include "3DObjectIrrAdapter.h"
#include "MDA.h"

class Stage : public IDrawer{
public:
	Stage(){
		m_drawer.setResouceName(_T("./space/back.x"));
		Glas::Vector3f v;
		std::fill(v.begin(),v.end(), 0);
		m_drawer.setPosition(v);
		m_drawer.setScale(30);
	}
	bool isVisible(){return true;};
	void draw(){
		m_drawer.draw();
	};
	void setPosition(Glas::Vector3f v){
		m_drawer.setPosition(v);
	}
private:
	Drawer3DImpl m_drawer;
};