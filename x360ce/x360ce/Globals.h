#pragma once

class Globals
{
public:
	static bool dInputEnabled;
	static DWORD dInputLibrary;
	static GUID dInputPlayerGuid;
	static bool dInputForceDisable;

	static bool xInputEnabled;
	static DWORD xInputPlayerId;
	static bool xInputReRouteEnabled;
	static DWORD xInputReRouteTemplate;

	//static bool blockInputEvents;
	//static bool blockMouseEvents;
	//static bool blockKeyboardEvents;

	static bool enableMKBInput;

	static bool forceFocus;
	static std::wstring* forceFocusWindowRegex;

	// signed long!
	static long windowY;
	static long windowX;
	static DWORD resWidth;
	static DWORD resHeight;

	static bool fixResolution;
	static bool fixPosition;
	static bool clipMouse;

	static bool hasHooked;

	static bool hasSetPosition;
	static bool hasSetSize;
	static bool hasSetStyle;
	static bool hasSetEverything;
};
