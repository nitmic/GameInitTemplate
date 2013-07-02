#pragma once
#include <RingBuffer.hpp>

class AnalogStick{
public:
	void update(float x, float y);
	Blas::Vector2f getTilt(){return m_Tilt.current();};
private:
	TUL::RingBuffer<Blas::Vector2f,3> m_Tilt;
};

