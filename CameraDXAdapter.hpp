#pragma once
#include <DXCamera.h>
#include "GLAS.h"

namespace DXAdapter{
	template<class T>
	class Camera : public T{
	public:
		void transform(){
			auto lookat = getAttitude() * Glas::Vector3f(0, 0, 1) + getPosition();
			auto virtical = getAttitude() * Glas::Vector3f(0, 1, 0);
			m_Camera.setLookAt(lookat.X, lookat.Y, lookat.Z);
			m_Camera.setPosition(getPosition().X, getPosition().Y, getPosition().Z);
			m_Camera.setTilt(virtical.X,virtical.Y, virtical.Z);
			m_Camera.transform();
		}
	private:
		DXLib::DXCamera m_Camera;
	};
};