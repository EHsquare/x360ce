#include "stdafx.h"
#include "dinputHook.h"


dinputHook::dinputHook()
{
}


dinputHook::~dinputHook()
{
}

// Direct Input crap
//typedef signed int(__stdcall* CDIObj_EnumObjectsWProc)(int, LPDIENUMDEVICEOBJECTSCALLBACK, int, unsigned int);
//typedef signed int(__stdcall* CDIObj_CreateDeviceWProc)(int, REFGUID, LPDIRECTINPUTDEVICE, LPUNKNOWN);
//typedef int(_stdcall* CDIDev_SetCooperativeLevelProc)(LPDIRECTINPUTDEVICE, HWND, int);
//typedef signed int(__fastcall* JoyReg_GetConfigProc)(unsigned int, UINT, LPDIJOYCONFIG, DWORD);
//typedef HRESULT(__thiscall* CDIDev_GetDeviceStateProc)(void*, IDirectInputDevice2W*, int, int);
//typedef HRESULT(__thiscall* CDIDev_PollProc)(void*);
//typedef HRESULT(__stdcall* CDIDev_SetDataFormatProc)(int*, int);
//typedef HRESULT(__stdcall* DirectInputCreateWProc)(HINSTANCE, DWORD, LPDIRECTINPUTW*, LPUNKNOWN);
//CDIObj_EnumObjectsWProc TrueCDIObj_EnumObjectsW = nullptr;
//CDIObj_CreateDeviceWProc TrueCDIObj_CreateDeviceW = nullptr;
//CDIDev_GetDeviceStateProc TrueCDIDev_GetDeviceState = nullptr;
//JoyReg_GetConfigProc TrueJoyReg_GetConfig = nullptr;
//CDIDev_SetCooperativeLevelProc TrueCDIDev_SetCooperativeLevel = nullptr;
//CDIDev_SetDataFormatProc TrueCDIDev_SetDataFormat = nullptr;
//CDIDev_PollProc TrueCDIDev_Poll = nullptr;
//DirectInputCreateWProc TrueDirectInputCreateW = nullptr;
//LPDIRECTINPUTDEVICE DevicePtr;
//LPDIENUMDEVICEOBJECTSCALLBACK tempCallback;

// dinput.dll hooks
//HRESULT HookDirectInputCreateW(HINSTANCE hInst, DWORD dwVersion, LPDIRECTINPUTW* ppDI, LPUNKNOWN punkOuter)
//{
//	return DIERR_INVALIDPARAM;
//}
//NTSTATUS __stdcall HookHidP_GetButtonCaps(_In_    HIDP_REPORT_TYPE     ReportType,
//	_Out_   PHIDP_BUTTON_CAPS    ButtonCaps,
//	_Inout_ PUSHORT              ButtonCapsLength,
//	_In_    PHIDP_PREPARSED_DATA PreparsedData)
//{
//	PrintLog("HidP_GetButtonCaps");
//	return TrueHidP_GetButtonCaps(ReportType, ButtonCaps, ButtonCapsLength, PreparsedData);
//}
//
//NTSTATUS __stdcall HookHidP_GetUsages(_In_    HIDP_REPORT_TYPE     ReportType,
//	_In_    USAGE                UsagePage,
//	_In_    USHORT               LinkCollection,
//	_Out_   PUSAGE               UsageList,
//	_Inout_ PULONG               UsageLength,
//	_In_    PHIDP_PREPARSED_DATA PreparsedData,
//	_Out_   PCHAR                Report,
//	_In_    ULONG                ReportLength)
//{
//	PrintLog("HidP_GetUsages");
//	return TrueHidP_GetUsages(ReportType, UsagePage, LinkCollection, UsageList, UsageLength, PreparsedData, Report, ReportLength);
//}
//
//NTSTATUS __stdcall HookHidP_GetUsageValue(_In_  HIDP_REPORT_TYPE     ReportType,
//	_In_  USAGE                UsagePage,
//	_In_  USHORT               LinkCollection,
//	_In_  USAGE                Usage,
//	_Out_ PULONG               UsageValue,
//	_In_  PHIDP_PREPARSED_DATA PreparsedData,
//	_In_  PCHAR                Report,
//	_In_  ULONG                ReportLength)
//{
//	PrintLog("HidP_GetUsageValue");
//	return TrueHidP_GetUsageValue(ReportType, UsagePage, LinkCollection, Usage, UsageValue, PreparsedData, Report, ReportLength);
//}
//
//NTSTATUS __stdcall HookHidP_GetData(_In_ HIDP_REPORT_TYPE ReportType,
//	_Out_   PHIDP_DATA           DataList,
//	_Inout_ PULONG               DataLength,
//	_In_    PHIDP_PREPARSED_DATA PreparsedData,
//	_In_    PCHAR                Report,
//	_In_    ULONG                ReportLength)
//{
//	//PrintLog("HidP_GetData");
//	return TrueHidP_GetData(ReportType, DataList, DataLength, PreparsedData, Report, ReportLength);
//}
//
//HANDLE WINAPI HookCreateFile(_In_  LPCTSTR lpFileName,
//	_In_     DWORD                 dwDesiredAccess,
//	_In_     DWORD                 dwShareMode,
//	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//	_In_     DWORD                 dwCreationDisposition,
//	_In_     DWORD                 dwFlagsAndAttributes,
//	_In_opt_ HANDLE                hTemplateFile)
//{
//	//PrintLog("CreateFile " + CStringA(lpFileName));
//	return TrueCreateFileProc(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
//}
//
//int HookCHid_GetDeviceState(int* a, void* dst)
//{
//	PrintLog(("HookCHid_GetDeviceState A:" + std::to_string((DWORD)a)).c_str());
//	return TrueCHid_GetDeviceState(a, dst);
//}
//extern "C" bool __stdcall HookCDIObj_EnumObjectsWCallback(DIDEVICEOBJECTINSTANCEW* instance, void* function)
//{
//	return DIENUM_CONTINUE;
//}
//
//extern "C" signed int __stdcall HookCDIObj_EnumObjectsW(int a1, LPDIENUMDEVICEOBJECTSCALLBACK callback, int a3, unsigned int a4)
//{
//	tempCallback = callback;
//	int retValue = TrueCDIObj_EnumObjectsW(a1, (LPDIENUMDEVICEOBJECTSCALLBACK)HookCDIObj_EnumObjectsWCallback, a3, a4);
//	tempCallback = nullptr;
//
//	return retValue;
//}
//
//
//extern "C" signed int __stdcall HookCDIObj_CreateDeviceW_Disabled(int a1, REFGUID rguid, LPDIRECTINPUTDEVICE device, LPUNKNOWN pUnkOuter)
//{
//	return DIERR_OUTOFMEMORY;
//}
//
//extern "C" signed int __stdcall HookCDIObj_CreateDeviceW(int a1, REFGUID rguid, LPDIRECTINPUTDEVICE device, LPUNKNOWN pUnkOuter)
//{
//	GUID iguid = rguid;
//	if (iguid == Globals::dInputPlayerGuid && GameHWND != NULL)
//	{
//		int result = TrueCDIObj_CreateDeviceW(a1, rguid, device, pUnkOuter);
//		DevicePtr = device;
//
//		//IDirectInputDevice2W* test = (IDirectInputDevice2W*)device;
//		//Sleep(100);
//		//HRESULT res = device->SetCooperativeLevel(GameHWND, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
//		//TrueCDIDev_SetCooperativeLevel(device, GameHWND, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
//
//		return result;
//	}
//	else
//	{
//		// noooope we dont allow you to access this gamepad
//		return DIERR_OUTOFMEMORY;
//	}
//}
//
//extern "C" signed int __fastcall HookJoyReg_GetConfig_Disabled(unsigned int a1, UINT uiJoy, LPDIJOYCONFIG pjc, DWORD dwFlags)
//{
//	return DIERR_NOMOREITEMS;
//}
//
//extern "C" signed int __fastcall HookJoyReg_GetConfig(unsigned int a1, UINT uiJoy, LPDIJOYCONFIG pjc, DWORD dwFlags)
//{
//	return DIERR_NOMOREITEMS;
//
//	if (a1 == 0)
//	{
//		// How this works:
//		// On DirectInput devices, there's a freakin hidden property that is the primary gamepad.
//		// That gamepad is always in the 0 ID.
//		// So when the application requests our gamepad ID, we only show the first
//		for (int i = 0;; i++)
//		{
//			signed int result = TrueJoyReg_GetConfig(i, uiJoy, pjc, dwFlags);
//			if (result == DIERR_NOMOREITEMS)
//			{
//				break;
//			}
//
//			if (pjc->guidInstance == Globals::dInputPlayerGuid)
//			{
//				return result;
//			}
//		}
//	}
//	else
//	{
//		return DIERR_NOMOREITEMS;
//	}
//}
//
//HRESULT __fastcall HookCDIDev_GetDeviceState(void* This, void* notUsed, IDirectInputDevice2W* pDevice, int cbData, int lpvData)
//{
//	if (!SetGamepad)
//	{
//		DevicePtr = pDevice;
//
//		// before setting, change the cooperative level
//		pDevice->Unacquire();
//		HRESULT result = pDevice->SetCooperativeLevel(GameHWND, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
//
//		SetGamepad = true;
//	}
//
//	DIDEVICEINSTANCEW instance;
//	instance.dwSize = sizeof(DIDEVICEINSTANCEW);
//	pDevice->GetDeviceInfo(&instance);
//
//	GUID iguid = instance.guidInstance;
//	if (iguid == Globals::dInputPlayerGuid)
//	{
//		return TrueCDIDev_GetDeviceState(This, pDevice, cbData, lpvData);
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//HRESULT __fastcall HookCDIDev_Poll(LPDIRECTINPUTDEVICE8 device, void* notUsed)
//{
//	return device->Acquire();
//}
//
//
//int __stdcall HookCDIDev_SetCooperativeLevel(LPDIRECTINPUTDEVICE a1, HWND hWnd, int a3)
//{
//	return TrueCDIDev_SetCooperativeLevel(a1, hWnd, a3);
//}
//
//HRESULT __fastcall HookCDIDev_SetDataFormat(int* a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
//{
//	LPDIRECTINPUTDEVICE dev = (LPDIRECTINPUTDEVICE)a6;
//	LPCDIDATAFORMAT data4 = (LPCDIDATAFORMAT)a4;
//	return TrueCDIDev_SetDataFormat((int*)a6, a4);
//}
