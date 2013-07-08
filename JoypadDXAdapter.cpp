#include "JoypadDXAdapter.h"
#include <Singleton.hpp>
#include <DXJoypad.h>
#include <DXStdafx.h>

#pragma warning(disable:4482)
#pragma warning(disable:4800)


void DXAdapter::Joypad::update(){
	auto pad = GetSingleton<DXLib::DXJoypad>();
	setButton(DefaultButton::A,       pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::A) & 0x80);
	setButton(DefaultButton::B,       pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::B) & 0x80);
	setButton(DefaultButton::X,       pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::X) & 0x80);
	setButton(DefaultButton::Y,       pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Y) & 0x80);
	setButton(DefaultButton::Select,  pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Select) & 0x80);
	setButton(DefaultButton::Start,   pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Start) & 0x80);
	setButton(DefaultButton::Up,      pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Up) & 0x80);
	setButton(DefaultButton::Down,    pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Down) & 0x80);
	setButton(DefaultButton::Left,    pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Left) & 0x80);
	setButton(DefaultButton::Right,   pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::Right) & 0x80);
	setButton(DefaultButton::L1,    pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::L1) & 0x80);
	setButton(DefaultButton::R1,   pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::R1) & 0x80);
	setButton(DefaultButton::L2,    pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::L2) & 0x80);
	setButton(DefaultButton::R2,   pad->getButtonState(m_PlayerNum, DXLib::DXJoypad::R2) & 0x80);
	auto x = pad->getLAnalogStickState(m_PlayerNum);
	setLStick(x.x / DXLib::DXJoypad::DX_PROP_MAX, x.y / DXLib::DXJoypad::DX_PROP_MAX);
	auto y = pad->getRAnalogStickState(m_PlayerNum);
	setRStick(y.x / DXLib::DXJoypad::DX_PROP_MAX, y.y / DXLib::DXJoypad::DX_PROP_MAX);
}