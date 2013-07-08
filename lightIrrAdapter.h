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
		Light(){
			m_pNode = GetSingleton<IrrApp>()->accessSceneManager()->addLightSceneNode(
				nullptr, Glas::Vector3f(0,0,-10), irr::video::SColorf(0xFFFFFFFF), 10.0f
			);
		}
		~Light(){
			m_pNode->remove();
		}
		void setLightDirection(Glas::Vector3f d){
			//
		}
		void draw(){
			m_pNode->setVisible(true);
		}
		void draw(Glas::Vector3f d){
			setLightDirection(d);
			draw();
		}
	};
};