#pragma once
#include <DXCamera.h>

namespace DXAdapter{
	template<class T>
	class Camera : public T{
	public:
		void transform(){
			m_Camera.setLookAt(getLookAt()[0], getLookAt()[1], getLookAt()[2]);
			m_Camera.setPosition(getPosition()[0], getPosition()[1], getPosition()[2]);
			m_Camera.setTilt(getVirtical()[0],getVirtical()[1], getVirtical()[2]);
			m_Camera.transform();
		}
	private:
		DXLib::DXCamera m_Camera;
	};
};