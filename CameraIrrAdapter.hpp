#pragma once
#include "GLAS.h"
#include <Singleton.hpp>
#include "IrrAdapter.h"
#include <ICameraSceneNode.h>
#include "Debug.h"

namespace IrrAdapter{
	template<class T>
	class Camera : public T{
	public:
		Camera(){
			m_Node = GetSingleton<IrrApp>()->accessSceneManager()->addCameraSceneNode(
				nullptr, Glas::Vector3f(0,0,-5), Glas::Vector3f(0,0,0)
			);
			m_Light = GetSingleton<IrrApp>()->accessSceneManager()->addLightSceneNode(
				nullptr, Glas::Vector3f(0,0,10), irr::video::SColorf(0xFFFFFFFF), 5.0f
			);
			m_Light->setLightType(irr::video::ELT_DIRECTIONAL);
		}
		~Camera(){
			m_Node->remove();
		}
		void transform(){
			m_Node->setVisible(true);
			m_Node->setPosition(getPosition());
			m_Node->setTarget(getLookAt());
			m_Node->setUpVector(getAttitude() * Glas::Vector3f(0,1,0));
			
			
			Glas::EulerAngle3r eular;
			getAttitude().toEuler(eular);
			m_Light->setRotation(Glas::Vector3f(
				((TUL::Degree)(eular.X)).getRaw(),
				((TUL::Degree)(eular.Y)).getRaw(),
				((TUL::Degree)(eular.Z)).getRaw()
			));
			m_Light->setPosition(getPosition() + getAttitude()*Glas::Vector3f(0,0,10));

			m_Light->setVisible(true);
		}
	private:
		irr::scene::ILightSceneNode * m_Light;
		irr::scene::ICameraSceneNode * m_Node;
	};
};