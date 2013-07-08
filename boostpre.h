#pragma once

#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

#include <array>
#include <algorithm>
#include <functional>
#include <memory>
#include <assert.h>
#include <vector>
#include <map>


namespace IrrAdapter{};
namespace DXAdapter{
	class Joypad;
};


using DXAdapter::Joypad;
using namespace IrrAdapter;
