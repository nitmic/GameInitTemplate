#pragma once
#include "DXMesh.h"
#include "MDA.h"
#include <algorithm>

namespace DXAdapter{
	class Drawer3DImpl{
	private:
		tString m_name;
		Blas::Vector3f m_Pos;
		Blas::Vector3f m_Virtical;
		Blas::Vector3f m_Direction;
		Blas::Vector3f m_Scale;
	public:
		Drawer3DImpl(){
			m_Virtical[0] = 0;
			m_Virtical[1] = 1;
			m_Virtical[2] = 0;
			m_Direction[0] = 0;
			m_Direction[1] = 0;
			m_Direction[2] = 1;
			std::fill(m_Scale.begin(), m_Scale.end(), 1);
		};
		void setPosition(Blas::Vector3f pos);
		void setVirtical(Blas::Vector3f virtical);
		void setDirection(Blas::Vector3f direction);
		void setScale(float amount);
		void setResouceName(tString name);
		void draw();
	};
};