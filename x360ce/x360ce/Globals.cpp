#include "stdafx.h"
#include "Globals.h"

Globals* Globals::single = nullptr;

Globals* Globals::GetInstance()
{
	if (single == nullptr)
	{
		single = new Globals();
	}
	return single;
}