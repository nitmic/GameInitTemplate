#pragma once
#include <tString.h>
#include "AnalogStick.h"
#include "Button.h"



class AbsJoypad{
public:
	virtual void update() = 0;
	enum DefaultButton{
		A, B, X, Y, L1, L2, R1, R2, Select, Start, Up, Right, Down, Left
	};
	AnalogStick & getLStick();
	AnalogStick & getRStick();
	Button & getButton(DefaultButton button);
	void applyKeyConfig(tString filename);
protected:
	void setLStick(float x, float y);
	void setRStick(float x, float y);
	void setButton(DefaultButton name, bool b);
private:
	std::map<int,Button> m_Buttons;
	AnalogStick m_LStick;
	AnalogStick m_RStick;
};