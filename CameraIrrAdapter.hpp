#pragma once
#include "GLAS.h"
#include <Singleton.hpp>
#include "IrrAdapter.h"
#include <ICameraSceneNode.h>

namespace IrrAdapter{
	template<class T>
	class Camera : public T{
	public:
		Camera(){
			m_Node = GetSingleton<IrrApp>()->accessSceneManager()->addCameraSceneNode(
				nullptr, Glas::Vector3f(0,0,-5), Glas::Vector3f(0,0,0)
			);
		}
		~Camera(){
			m_Node->remove();
		}
		void transform(){
			m_Node->setVisible(true);
			m_Node->setPosition(getPosition());

			Glas::EulerAngle3r eular;
			getAttitude().toEuler(eular);
			m_Node->setRotation(Glas::Vector3f(
				((TUL::Degree)(eular.X)).getRaw(),
				((TUL::Degree)(eular.Y)).getRaw(),
				((TUL::Degree)(eular.Z)).getRaw()
			));
		}
	private:
		irr::scene::ICameraSceneNode * m_Node;
	};
};