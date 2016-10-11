/*  x360ce - XBOX360 Controller Emulator
 *
 *  https://code.google.com/p/x360ce/
 *
 *  Copyright (C) 2002-2010 Racer_S
 *  Copyright (C) 2010-2014 Robert Krawczyk
 *
 *  x360ce is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or any later version.
 *
 *  x360ce is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with x360ce.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "Common.h"

#include "InputHook.h"
#include "Config.h"

#include "ForceFeedbackBase.h"
#include "ForceFeedback.h"
#include "ControllerBase.h"
#include "Controller.h"
#include "ControllerCombiner.h"

#include "XInputModuleManager.h"
#include "Globals.h"

bool Hooked = false;
std::vector<HWND> UpdatedWnd = std::vector<HWND>();
typedef HWND(WINAPI* GetForegroundProc)(void);
typedef bool(WINAPI* SetForegroundProc)(HWND);
typedef HWND(WINAPI* SetActiveProc)(HWND);

WNDPROC TrueWndProc = nullptr;
HWND GameHWND = nullptr;
GetForegroundProc TrueGetForegroundWindow = nullptr;
SetForegroundProc TrueSetForegroundWindow = nullptr;
SetActiveProc TrueSetActiveWindow = nullptr;

LRESULT CALLBACK HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETFOCUS: // wParam = handle to the window that lost focus
	case WM_KILLFOCUS:
	case 144:
	case 5374:
	case WM_CAPTURECHANGED:
	case WM_NCACTIVATE:
	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
		return 0;

		// Borderlands only received these in my tests
#ifdef NOKB
	case WM_MOUSEMOVE:
	{
		return CallWindowProc(TrueWndProc, hWnd, message, wParam, 0);
	}
#else
	case WM_MOUSEMOVE:
#endif
	case WM_SETCURSOR:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_NCMOUSEMOVE:
	case WM_NCMOUSELEAVE:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_NCLBUTTONDOWN:
#ifdef NOKB
		return 0;
#endif

	case WM_NCHITTEST:
	case WM_GETICON:

	case WM_SYSCOMMAND:
	case WM_GETMINMAXINFO:
	case WM_ENTERSIZEMOVE:
	case WM_MOVING:
	case WM_WINDOWPOSCHANGING:
	case WM_WINDOWPOSCHANGED:
	case WM_MOVE:
	case WM_EXITSIZEMOVE:
	case WM_IME_SETCONTEXT:
	case WM_IME_NOTIFY:
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_NCDESTROY:

	default:
	case WM_CANCELMODE:
	case WM_ENABLE:
	case WM_AFXFIRST:
	case WM_AFXLAST:
	case WM_APP:
	case WM_APPCOMMAND:
	case WM_ASKCBFORMATNAME:
	case WM_CANCELJOURNAL:
	case WM_CHANGECBCHAIN:
	case WM_CHANGEUISTATE:
	case WM_CLEAR:
	case WM_COMMAND:
	case WM_COMMNOTIFY:
	case WM_COMPACTING:
	case WM_COMPAREITEM:
	case WM_CONTEXTMENU:
	case WM_COPY:
	case WM_COPYDATA:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
	case WM_CUT:
	case WM_DELETEITEM:
	case WM_DESTROYCLIPBOARD:
	case WM_DEVICECHANGE:
	case WM_DEVMODECHANGE:
	case WM_DISPLAYCHANGE:
	case WM_DRAWCLIPBOARD:
	case WM_DRAWITEM:
	case WM_DROPFILES:
	case WM_ENDSESSION:
	case WM_ENTERIDLE:
	case WM_ENTERMENULOOP:
	case WM_ERASEBKGND:
	case WM_EXITMENULOOP:
	case WM_FONTCHANGE:
	case WM_GETDLGCODE:
	case WM_GETFONT:
	case WM_GETHOTKEY:
	case WM_GETOBJECT:
	case WM_GETTEXT:
	case WM_GETTEXTLENGTH:
	case WM_HANDHELDFIRST:
	case WM_HANDHELDLAST:
	case WM_HELP:
	case WM_HOTKEY:
	case WM_HSCROLLCLIPBOARD:
	case WM_ICONERASEBKGND:
	case WM_IME_CHAR:
	case WM_IME_COMPOSITION:
	case WM_IME_COMPOSITIONFULL:
	case WM_IME_CONTROL:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_KEYDOWN:
	case WM_IME_KEYUP:
	case WM_IME_REQUEST:
	case WM_IME_SELECT:
	case WM_IME_STARTCOMPOSITION:
	case WM_INITDIALOG:
	case WM_INITMENU:
	case WM_INITMENUPOPUP:
	case WM_INPUT:
	case WM_INPUTLANGCHANGE:
	case WM_INPUTLANGCHANGEREQUEST:
	case WM_KEYLAST:
	case WM_MDIACTIVATE:
	case WM_MDICASCADE:
	case WM_MDICREATE:
	case WM_MDIDESTROY:
	case WM_MDIGETACTIVE:
	case WM_MDIICONARRANGE:
	case WM_MDIMAXIMIZE:
	case WM_MDINEXT:
	case WM_MDIREFRESHMENU:
	case WM_MDIRESTORE:
	case WM_MDISETMENU:
	case WM_MDITILE:
	case WM_MEASUREITEM:
	case WM_MENUCHAR:
	case WM_MENUCOMMAND:
	case WM_MENUDRAG:
	case WM_MENUGETOBJECT:
	case WM_MENURBUTTONUP:
	case WM_MENUSELECT:
	case WM_NCCALCSIZE:
	case WM_NCCREATE:
	case WM_NCPAINT:
	case WM_NEXTDLGCTL:
	case WM_NEXTMENU:
	case WM_NOTIFY:
	case WM_NOTIFYFORMAT:
	case WM_NULL:
	case WM_PAINT:
	case WM_PAINTCLIPBOARD:
	case WM_PAINTICON:
	case WM_PALETTECHANGED:
	case WM_PALETTEISCHANGING:
	case WM_PARENTNOTIFY:
	case WM_PASTE:
	case WM_PENWINFIRST:
	case WM_PENWINLAST:
	case WM_POWER:
	case WM_POWERBROADCAST:
	case WM_PRINT:
	case WM_PRINTCLIENT:
	case WM_QUERYDRAGICON:
	case WM_QUERYENDSESSION:
	case WM_QUERYNEWPALETTE:
	case WM_QUERYOPEN:
	case WM_QUERYUISTATE:
	case WM_QUEUESYNC:
	case WM_RENDERALLFORMATS:
	case WM_RENDERFORMAT:
	case WM_SETFONT:
	case WM_SETHOTKEY:
	case WM_SETICON:
	case WM_SETREDRAW:
	case WM_SETTEXT:
	case WM_SETTINGCHANGE:
	case WM_SHOWWINDOW:
	case WM_SIZE:
	case WM_SIZECLIPBOARD:
	case WM_SIZING:
	case WM_SPOOLERSTATUS:
	case WM_STYLECHANGED:
	case WM_STYLECHANGING:
	case WM_SYNCPAINT:
	case WM_SYSCHAR:
	case WM_SYSCOLORCHANGE:
	case WM_SYSDEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_TABLET_FIRST:
	case WM_TABLET_LAST:
	case WM_TCARD:
	case WM_THEMECHANGED:
	case WM_TIMECHANGE:
	case WM_TIMER:
	case WM_UNDO:
	case WM_UNINITMENUPOPUP:
	case WM_UPDATEUISTATE:
	case WM_USER:
	case WM_USERCHANGED:
	case WM_VKEYTOITEM:
	case WM_VSCROLL:
	case WM_VSCROLLCLIPBOARD:
	case WM_WTSSESSION_CHANGE:
	case WM_XBUTTONDBLCLK:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEACTIVATE:
	case WM_MOUSEHOVER:
	case WM_MOUSELAST:
	case WM_MOUSELEAVE:
	case WM_MOUSEWHEEL:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_HSCROLL:
	case WM_NCMOUSEHOVER:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCLBUTTONUP:
	case WM_NCMBUTTONDBLCLK:
	case WM_NCMBUTTONDOWN:
	case WM_NCMBUTTONUP:
	case WM_NCRBUTTONDBLCLK:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONUP:
	case WM_NCXBUTTONDBLCLK:
	case WM_NCXBUTTONDOWN:
	case WM_NCXBUTTONUP:
	case WM_CHARTOITEM:
	case WM_DEADCHAR:
	case WM_CREATE:
	case WM_CHILDACTIVATE:
	case WM_QUIT:
	{
		std::string st = "MESSAGE: " + std::to_string(message);
		PrintLog(st.c_str());
		return CallWindowProc(TrueWndProc, hWnd, message, wParam, lParam);
		//return 0;
	}
	}
}

HWND HookGetForegroundWindow()
{
	return GameHWND;
}

bool HookSetForegroundWindow(HWND hWnd)
{
	return true;
}

HWND HookSetActiveWindow(HWND hWnd)
{
	return NULL;
}

struct EnumWindowsCallbackArgs {
	EnumWindowsCallbackArgs(DWORD p) : pid(p) { }
	const DWORD pid;
	std::vector<HWND> handles;
};

static BOOL CALLBACK EnumWindowsCallback(HWND hnd, LPARAM lParam)
{
	EnumWindowsCallbackArgs *args = (EnumWindowsCallbackArgs *)lParam;

	DWORD windowPID;
	(void)::GetWindowThreadProcessId(hnd, &windowPID);
	if (windowPID == args->pid) {
		args->handles.push_back(hnd);
	}

	return TRUE;
}

std::vector<HWND> getToplevelWindows()
{
	EnumWindowsCallbackArgs args(::GetCurrentProcessId());
	if (::EnumWindows(&EnumWindowsCallback, (LPARAM)&args) == FALSE) {
		// XXX Log error here
		return std::vector<HWND>();
	}
	return args.handles;
}

extern "C" DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	if (!Hooked)
	{
		Globals* global = Globals::GetInstance();

		if (global->HookNeeded())
		{
			int wait = global->HookWindows();

			std::vector<HWND> windows = getToplevelWindows();
			size_t size = windows.size();
			if (size == wait || wait == -1)
			{
				GameHWND = windows[global->HookGameWindow()];
				TrueWndProc = (WNDPROC)SetWindowLongPtr(GameHWND, GWL_WNDPROC, (LONG_PTR)&HookWndProc);
				Hooked = true;

				HMODULE mod = LoadLibrary("user32");
				void* getForegroundPtr = GetProcAddress(mod, "GetForegroundWindow");
				void* setForegroundPtr = GetProcAddress(mod, "SetForegroundWindow");
				void* setActivePtr = GetProcAddress(mod, "SetActiveWindow");

				MH_Initialize();

				IH_CreateHook(getForegroundPtr, HookGetForegroundWindow, reinterpret_cast<LPVOID*>(&TrueGetForegroundWindow));
				IH_EnableHook(getForegroundPtr);

				IH_CreateHook(setForegroundPtr, HookSetForegroundWindow, reinterpret_cast<LPVOID*>(&TrueSetForegroundWindow));
				IH_EnableHook(setForegroundPtr);

				IH_CreateHook(setActivePtr, HookSetActiveWindow, reinterpret_cast<LPVOID*>(&TrueSetActiveWindow));
				IH_EnableHook(setActivePtr);

				PrintLog("Hooked to game window");
#ifdef PLAYER1
				PrintLog("Player 1");
#elif PLAYER2
				PrintLog("Player 2");
#elif PLAYER3
				PrintLog("Player 3");
#elif PLAYER4
				PrintLog("Player 4");
#endif
			}
		}
	}


	if (dwUserIndex == 0)
	{
#ifdef PLAYER1
		return XInputModuleManager::Get().XInputGetState(0, pState);
#elif PLAYER2
		return XInputModuleManager::Get().XInputGetState(1, pState);
#elif PLAYER3
		return XInputModuleManager::Get().XInputGetState(2, pState);
#elif PLAYER4
		return XInputModuleManager::Get().XInputGetState(3, pState);
#endif
	}

	return XInputModuleManager::Get().XInputGetState(0, pState);


	return ERROR_DEVICE_NOT_CONNECTED;

	//PrintLog("XInputGetState");

	ControllerBase* pController;
	if (!pState)
		return ERROR_BAD_ARGUMENTS;
	u32 initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetState(pState);
}

extern "C" DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
	ControllerBase* pController;
	if (!pVibration)
		return ERROR_BAD_ARGUMENTS;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->SetState(pVibration);
}

extern "C" DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
	// Validate
	if (!pCapabilities || dwFlags != 0 && dwFlags != XINPUT_FLAG_GAMEPAD)
	{
		return ERROR_BAD_ARGUMENTS;
	}

	// Get controller
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);

	// If problem initializing controller, bail
	if (initFlag != ERROR_SUCCESS)
	{
		return initFlag;
	}

	return pController->GetCapabilities(dwFlags, pCapabilities);
}

extern "C" VOID WINAPI XInputEnable(BOOL enable)
{
	// If any controller is native XInput then use state too.
	for (auto it = ControllerManager::Get().GetControllers().begin(); it != ControllerManager::Get().GetControllers().end(); ++it)
	{
		if ((*it)->m_passthrough)
			XInputModuleManager::Get().XInputEnable(enable);
	}

	ControllerManager::Get().XInputEnable(enable);
}

extern "C" DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
	ControllerBase* pController;
	if (!pDSoundRenderGuid || !pDSoundCaptureGuid)
		return ERROR_BAD_ARGUMENTS;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetDSoundAudioDeviceGuids(pDSoundRenderGuid, pDSoundCaptureGuid);
}

extern "C" DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation)
{
	ControllerBase* pController;
	if (!pBatteryInformation)
		return ERROR_BAD_ARGUMENTS;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetBatteryInformation(devType, pBatteryInformation);
}

extern "C" DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, XINPUT_KEYSTROKE* pKeystroke)
{
	ControllerBase* pController;
	if (!pKeystroke)
		return ERROR_BAD_ARGUMENTS;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetKeystroke(dwReserved, pKeystroke);
}

//undocumented
extern "C" DWORD WINAPI XInputGetStateEx(DWORD dwUserIndex, XINPUT_STATE *pState)
{
	ControllerBase* pController;
	if (!pState)
		return ERROR_BAD_ARGUMENTS;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetStateEx(pState);
}

extern "C" DWORD WINAPI XInputWaitForGuideButton(DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->WaitForGuideButton(dwFlag, pVoid);
}

extern "C" DWORD WINAPI XInputCancelGuideButtonWait(DWORD dwUserIndex)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->CancelGuideButtonWait();
}

extern "C" DWORD WINAPI XInputPowerOffController(DWORD dwUserIndex)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->PowerOffController();
}

extern "C" DWORD WINAPI XInputGetAudioDeviceIds(DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetAudioDeviceIds(pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
}

extern "C" DWORD WINAPI XInputGetBaseBusInformation(DWORD dwUserIndex, struct XINPUT_BUSINFO* pBusinfo)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetBaseBusInformation(pBusinfo);
}

// XInput 1.4 uses this in XInputGetCapabilities and calls memcpy(pCapabilities, &CapabilitiesEx, 20u);
// so XINPUT_CAPABILITIES is first 20 bytes of XINPUT_CAPABILITIESEX
extern "C" DWORD WINAPI XInputGetCapabilitiesEx(DWORD unk1 /*seems that only 1 is valid*/, DWORD dwUserIndex, DWORD dwFlags, struct XINPUT_CAPABILITIESEX* pCapabilitiesEx)
{
	ControllerBase* pController;
	DWORD initFlag = ControllerManager::Get().DeviceInitialize(dwUserIndex, &pController);
	if (initFlag != ERROR_SUCCESS)
		return initFlag;

	return pController->GetCapabilitiesEx(unk1, dwFlags, pCapabilitiesEx);
}
