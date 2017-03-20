#pragma once

class Globals
{
private:
	static Globals *single;
	Globals()
	{
	}

	bool hookNeeded = false;
	char* gameWindowName;
	int playerOverride;

public:
	static Globals* GetInstance();
	~Globals()
	{
	}

	char* GetGameWindowName()
	{
		return gameWindowName;
	}
	void SetGameWindowName(char* value)
	{
		gameWindowName = value;
	}

	bool GetHookNeeded()
	{
		return hookNeeded;
	}
	void SetHookNeeded(bool value)
	{
		hookNeeded = value;
	}

	int GetPlayerOverride()
	{
		return playerOverride;
	}
	void SetPlayerOVerride(int value)
	{
		playerOverride = value;
	}
};