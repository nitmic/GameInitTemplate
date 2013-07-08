#pragma once
#include <RingBuffer.hpp>
#include "GLAS.h"

class AnalogStick{
public:
	void update(float x, float y);
	Glas::Vector2f getTilt(){return m_Tilt.current();};
private:
	TUL::RingBuffer<Glas::Vector2f,3> m_Tilt;
};

