#pragma once
#include "SDL.h"

class DeltaTime
{
private:
	int ticks;
	int oldTicks;

public:
	float Time = 0;

	DeltaTime();
	~DeltaTime();

	void UpdateDeltaTime();
	float GetDeltaTime();
};

