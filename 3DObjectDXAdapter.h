#pragma once
#include "DXMesh.h"
#include "MDA.h"
#include "GLAS.h"

namespace DXAdapter{
	class Drawer3DImpl{
	private:
		tString m_name;
		Glas::Vector3f m_Pos;
		Glas::Quaternion m_Attitude;
		Glas::Vector3f m_Scale;
	public:
		Drawer3DImpl(){
			std::fill(m_Scale.begin(), m_Scale.end(), 1);
		};
		void setPosition(Glas::Vector3f pos);
		void setAttitude(Glas::Quaternion attitude);
		void setScale(float amount);
		void setResouceName(tString name);
		void draw();
	};
};