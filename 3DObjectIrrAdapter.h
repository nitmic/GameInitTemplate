#pragma once
#include <tString.h>
#include "MDA.h"
#include "GLAS.h"
#include <Singleton.hpp>
#include "IrrAdapter.h"

namespace IrrAdapter{
	class Drawer3DImpl{
	private:
		irr::scene::IMeshSceneNode * m_Node;
		tString m_name;
		Glas::Vector3f m_Pos;
		Glas::Quaternion m_Attitude;
		Glas::Vector3f m_Scale;
	public:
		Drawer3DImpl(){
			std::fill(m_Scale.begin(), m_Scale.end(), 1);
			m_Node = GetSingleton<IrrApp>()->accessSceneManager()->addMeshSceneNode(
				GetSingleton<IrrApp>()->accessSceneManager()->getMesh("astro.x")
			);
		};
		~Drawer3DImpl(){
			m_Node->remove();
		}
		void setPosition(Glas::Vector3f pos);
		void setAttitude(Glas::Quaternion attitude);
		void setScale(float amount);
		void setResouceName(tString name);
		void draw();
	};
};