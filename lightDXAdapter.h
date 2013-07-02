#pragma once
#include <DXRenderingEngineStorage.h>
#include <Singleton.hpp>

namespace DXAdapter{
	class Light{
	public:
		void setLightDirection(Blas::Vector3f d){
			D3DXVECTOR4 x;
			x[0] = d[0];
			x[1] = d[1];
			x[2] = d[2];
			x[3] = 0;
			m_Direction = x;
		}
		void draw(){
			GetSingleton<DXLib::DXRenderingEngineStorage>()->SetLightDirection(m_Direction);
		}
		void draw(Blas::Vector3f d){
			setLightDirection(d);
			draw();
		}
	private:
		D3DXVECTOR4 m_Direction;
	};
};