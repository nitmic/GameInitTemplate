#include "AnalogStick.h"


void AnalogStick::update(float x, float y){
	Blas::Vector2f v;
	v[0] = x; v[1] = y;
	m_Tilt.update(v);
}