#pragma once
#include "stdafx.h"
#include <dinputd.h>

class dinputHook
{
public:
	dinputHook();
	~dinputHook();

	typedef signed int(__stdcall* CDIObj_EnumObjectsWProc)(int, LPDIENUMDEVICEOBJECTSCALLBACK, int, unsigned int);
	typedef signed int(__stdcall* CDIObj_CreateDeviceWProc)(int, REFGUID, LPDIRECTINPUTDEVICE, LPUNKNOWN);
	typedef int(_stdcall* CDIDev_SetCooperativeLevelProc)(LPDIRECTINPUTDEVICE, HWND, int);
	typedef signed int(__fastcall* JoyReg_GetConfigProc)(unsigned int, UINT, LPDIJOYCONFIG, DWORD);
	typedef HRESULT(__thiscall* CDIDev_GetDeviceStateProc)(void*, IDirectInputDevice2W*, int, int);
	typedef HRESULT(__thiscall* CDIDev_PollProc)(void*);
	typedef HRESULT(__stdcall* CDIDev_SetDataFormatProc)(int*, int);
	typedef HRESULT(__stdcall* DirectInputCreateWProc)(HINSTANCE, DWORD, LPDIRECTINPUTW*, LPUNKNOWN);
	CDIObj_EnumObjectsWProc TrueCDIObj_EnumObjectsW = nullptr;
	CDIObj_CreateDeviceWProc TrueCDIObj_CreateDeviceW = nullptr;
	CDIDev_GetDeviceStateProc TrueCDIDev_GetDeviceState = nullptr;
	JoyReg_GetConfigProc TrueJoyReg_GetConfig = nullptr;
	CDIDev_SetCooperativeLevelProc TrueCDIDev_SetCooperativeLevel = nullptr;
	CDIDev_SetDataFormatProc TrueCDIDev_SetDataFormat = nullptr;
	CDIDev_PollProc TrueCDIDev_Poll = nullptr;
	DirectInputCreateWProc TrueDirectInputCreateW = nullptr;
	LPDIRECTINPUTDEVICE DevicePtr;
	LPDIENUMDEVICEOBJECTSCALLBACK tempCallback;
};

