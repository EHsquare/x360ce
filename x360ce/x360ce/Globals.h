#pragma once

class Globals
{
private:
	static Globals *single;
	Globals()
	{
	}

	bool hookNeeded = false;
	int hookWindows = 0;
	int hookGameWindow = 0;

public:
	static Globals* GetInstance();
	~Globals()
	{
	}

	bool HookNeeded()
	{
		return hookNeeded;
	}
	void HookNeeded(bool value)
	{
		hookNeeded = value;
	}

	int HookWindows()
	{
		return hookWindows;
	}
	void HookWindows(int value)
	{
		hookWindows = value;
	}

	int HookGameWindow()
	{
		return hookGameWindow;
	}
	void HookGameWindow(int value)
	{
		hookGameWindow = value;
	}
};