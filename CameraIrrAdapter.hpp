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
				m_Node, Glas::Vector3f(0,0,10), irr::video::SColorf(0xFFFFFFFF), 5.0f
			);
			m_Light->setLightType(irr::video::ELT_DIRECTIONAL);
		}
		~Camera(){
			m_Node->remove();
		}
		void transform(){
			m_Node->setVisible(true);
			m_Node->setPosition(getPosition());
			
			Glas::EulerAngle3r eular;
			getAttitude().toEuler(eular);
			auto v = Glas::Vector3f(
				((TUL::Degree)(eular.X)).getRaw(),
				((TUL::Degree)(eular.Y)).getRaw(),
				((TUL::Degree)(eular.Z)).getRaw()
			);
			m_Node->setRotation(v);
			m_Light->setVisible(true);

			toStringStream ostr;
			ostr << _T("key: ") << v.X << _T(", ") << v.Y << _T(", ") << v.Z;
			Debug(ostr.str());

		}
	private:
		irr::scene::ILightSceneNode * m_Light;
		irr::scene::ICameraSceneNode * m_Node;
	};
};