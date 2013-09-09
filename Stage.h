#pragma once
#include "3DObjectIrrAdapter.h"
#include "MDA.h"

class Stage : public IDrawer{
public:
	Stage(){
		m_drawer.setResouceName(_T("./space/background.x"));
		m_Earth.setResouceName(_T("./space/earth.x"));
		
		Glas::Vector3f v;
		std::fill(v.begin(),v.end(), 0);
		m_drawer.setPosition(v);
		m_drawer.setScale(500);

		m_Earth.setPosition(v + Glas::Vector3f(0,0,2500));
		m_Earth.setScale(400);

	}
	bool isVisible(){return true;};
	void draw(){
		m_drawer.draw();
		m_Earth.draw();
	};
	void setPosition(Glas::Vector3f v){
		m_drawer.setPosition(v);
		m_Earth.setPosition(v + Glas::Vector3f(0,0,2500));
	}
private:
	Drawer3DImpl m_drawer;
	Drawer3DImpl m_Earth;
};