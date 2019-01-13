#include "stdafx.h"
#include "Globals.h"

//Globals* Globals::single = nullptr;
//
//Globals* Globals::GetInstance()
//{
//	if (single == nullptr)
//	{
//		single = new Globals();
//	}
//	return single;
//}

bool Globals::dInputEnabled = false;
DWORD Globals::dInputLibrary = 0;
GUID Globals::dInputPlayerGuid = GUID();
bool Globals::dInputForceDisable = false;

bool Globals::xInputEnabled = false;
DWORD Globals::xInputPlayerId = -1;
bool Globals::xInputReRouteEnabled = false;
DWORD Globals::xInputReRouteTemplate = 0;

//bool Globals::blockInputEvents = true;
//bool Globals::blockMouseEvents = true;
//bool Globals::blockKeyboardEvents = true;

bool Globals::enableMKBInput = true;

bool Globals::forceFocus = false;
std::wstring* Globals::forceFocusWindowRegex = nullptr;

DWORD Globals::windowY = 0;
DWORD Globals::windowX = 0;
DWORD Globals::resWidth = 0;
DWORD Globals::resHeight = 0;

bool Globals::fixResolution = false;
bool Globals::fixPosition = false;
bool Globals::clipMouse = false;

bool Globals::hasHooked = false;

bool Globals::hasSetStyle = false;
bool Globals::hasSetPosition = false;
bool Globals::hasSetSize = false;
bool Globals::hasSetEverything = false;
