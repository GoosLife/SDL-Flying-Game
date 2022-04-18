#pragma once
#include <SDL.h>
#include "DeltaTime.h"

class Clock
{
private:
	SDL_Rect mClockModel;
	float mVelocity;

public:
	Clock();
	~Clock();

	void Init(int spawnY, SDL_Window* window);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* ren);
};