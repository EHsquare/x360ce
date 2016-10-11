#include "stdafx.h"
#include "Common.h"
#include "Logger.h"
#include "Utils.h"

#include "Globals.h"

#include "Config.h"

#include "ControllerManager.h"
#include "InputHookManager.h"


VOID InitInstance()
{
#ifdef _DEBUG
	bool filelog = true;
	bool systemlog = true;
#else
	bool filelog = false;
	bool systemlog = false;
#endif

	if (systemlog)
	{
		LogSystem();
	}

	if (filelog)
	{
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		std::string processName;
		ModuleFileName(&processName);

		std::string logfile = StringFormat("x360ce_%s_%02u-%02u-%02u_%08u.log", processName.c_str(), systime.wYear,
			systime.wMonth, systime.wDay, GetTickCount());

		LogFile(logfile);
	}
	// Get will initalize static InputHookManager object and we want to initialize it ASAP
	InputHookManager::Get();

	IniFile ini;
	std::string inipath("ncoop.ini");
	ini.Load(inipath);
	//if (!ini.Load(inipath))
	//CheckCommonDirectory(&inipath, "x360ce");
	//if (!ini.Load(inipath)) return;

	int hookWindows;
	int hookGameWindow;
	bool hookNeeded;
	ini.Get("Options", "HookNeeded", &hookNeeded);
	ini.Get("Options", "HookWindows", &hookWindows);
	ini.Get("Options", "HookGameWindow", &hookGameWindow);

	Globals* global = Globals::GetInstance();
	global->HookNeeded(hookNeeded);
	global->HookWindows(hookWindows);
	global->HookGameWindow(hookGameWindow);

#ifdef _DEBUG
	PrintLog(("HookNeeded: " + std::to_string(hookNeeded)).c_str());
	PrintLog(("HookWindows: " + std::to_string(hookWindows)).c_str());
	PrintLog(("HookGameWindow: " + std::to_string(hookGameWindow)).c_str());
#endif
}

extern "C" VOID WINAPI Reset()
{
	PrintLog("Restarting");

	// Only x360ce.App will call this so InputHook is not required, disable it.
	InputHookManager::Get().GetInputHook().Shutdown();
	ControllerManager::Get().GetControllers().clear();
	ControllerManager::Get().GetConfig().ReadConfig();
}


extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			InitInstance();
			break;

		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
