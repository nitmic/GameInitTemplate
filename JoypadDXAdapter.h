#pragma once
#include "Joypad.h"
#include <tString.h>

namespace DXAdapter{
	class Joypad : public AbsJoypad{
	public:
		void update();
		Joypad(unsigned int playerNum) : m_PlayerNum(playerNum){};
		
	private:
		std::map<DefaultButton,int> keyConfig;
		unsigned int m_PlayerNum;
	};
};