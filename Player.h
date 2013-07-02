#pragma once
#include "MDA.h"
#include <Percentage.h>
#include <algorithm>

class Air{
public:
	Air() : m_rest(1){};
	bool isEmpty();
private:
	Percent m_rest;
};

class Life{
public:
	Life() : m_rest(1){};
	bool isEmpty();
private:
	Percent m_rest;
};

struct JetPower{
	JetPower(){
		direction[0] = 0;
		direction[1] = 0;
		power = 0;
	}
	Blas::Vector2f direction;
	float power;
};

class Player : public I3DModel{
public:
	bool isValid();
	Player(){
		std::fill(m_Pos.begin(), m_Pos.end(), 0);
		std::fill(m_Direction.begin(), m_Direction.end(), 0);
		m_Direction[2] = 1;
		std::fill(m_verticalDirection.begin(), m_verticalDirection.end(), 0);
		m_verticalDirection[1] = 1;
	}
	Blas::Vector3f getPosition();
	Blas::Vector3f getDirection(){return m_Direction;};
	Blas::Vector3f getVertical(){return m_verticalDirection;};
	
	void jetPropellant(JetPower jetL, JetPower jetR);

	void step();

	//void move(Blas::Vector3f v);
	Air getAir(){ return m_air;};
	Life getLife(){ return m_life;}
private:
	Air m_air;
	Life m_life;
	Blas::Vector3f m_Pos;
	Blas::Vector3f m_Direction;
	Blas::Vector3f m_verticalDirection;
};
