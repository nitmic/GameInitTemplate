#include "Player.h"

bool Air::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Life::isEmpty(){
	return Percent(0) >= m_rest;
}

bool Player::isValid(){
	return true;
}


Blas::Vector3f Player::getPosition(){
	return m_Pos;
}

void Player::step(){

}

void Player::jetPropellant(JetPower jetL, JetPower jetR){
	if(jetL.power){
		Blas::Vector2f a = jetL.power * jetL.direction;
		Blas::Vector3f b;
		b[0] = a[0];
		b[1] = a[1];
		b[2] = 0;
		this->m_Pos = this->m_Pos + b;
	}
	if(jetR.power){
		Blas::Vector2f a = jetR.power * jetR.direction;
		Blas::Vector3f b;
		b[0] = a[0];
		b[1] = a[1];
		b[2] = 0;
		this->m_Pos = this->m_Pos + b;
	}
}