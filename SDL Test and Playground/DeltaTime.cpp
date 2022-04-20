#include "DeltaTime.h"
DeltaTime::DeltaTime() {}
DeltaTime::~DeltaTime() {}

/// <summary>
/// Update delta time
/// </summary>
/// <returns></returns>
float DeltaTime::GetDeltaTime() {
	return Time;
}

void DeltaTime::UpdateDeltaTime() {
	oldTicks = ticks;
	ticks = SDL_GetTicks();

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), oldTicks + 16));

	Time = ((ticks - oldTicks) / 1000.0f);

	if (Time < 0.05f) {
		Time = 0.05f;
	}
	else if (Time > 100.0f) {
		Time = 0.05f;
	}
}