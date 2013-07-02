#include "Joypad.h"

void AbsJoypad::setButton(DefaultButton name, bool b){
	m_Buttons[name].update(b);
}

void AbsJoypad::setLStick(float x, float y){
	m_LStick.update(x,y);
}
void AbsJoypad::setRStick(float x, float y){
	m_RStick.update(x,y);
}
Button & AbsJoypad::getButton(DefaultButton button){
	return m_Buttons[button];
}

AnalogStick & AbsJoypad::getLStick(){
	return m_LStick;
}
AnalogStick &  AbsJoypad::getRStick(){
	return m_RStick;
}
