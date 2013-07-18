#pragma once
#include <Singleton.hpp>
#include "GLAS.h"
#include "IrrAdapter.h"
#include "ILightSceneNode.h"

namespace IrrAdapter{
	class Light{
	private:
		irr::scene::ILightSceneNode * m_pNode;
	public:
		enum Type{Point ,Spot, Directional};
		Light(){
			m_pNode = GetSingleton<IrrApp>()->accessSceneManager()->addLightSceneNode(
				nullptr, Glas::Vector3f(0,0,-10), irr::video::SColorf(0xFFFFFFFF),10.0f
			);
		}
		~Light(){
			m_pNode->remove();
		}
		void setLightDirection(Glas::EulerAngle3r d){
			m_pNode->setRotation(Glas::Vector3f(
				((TUL::Degree)(d.X)).getRaw(),
				((TUL::Degree)(d.Y)).getRaw(),
				((TUL::Degree)(d.Z)).getRaw()
			));
		}
		void setLightPosition(Glas::Vector3f p){
			m_pNode->setPosition(p);
		}
		void draw(){
			m_pNode->setVisible(true);
		}
		void draw(Glas::EulerAngle3r d, Glas::Vector3f p){
			setLightDirection(d);
			setLightPosition(p);
			draw();
		}
	};
};