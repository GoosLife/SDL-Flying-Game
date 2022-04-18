#pragma once
#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "Entity.h"

class SpawnManager
{
private:
	int mOldResult;
public:
	SpawnManager();
	~SpawnManager();

	void SpawnEntity(SDL_Window* window, std::list<Entity>* entities); // Spawns clocks, score objects or enemies

	void SpawnClock(int spawnY, SDL_Window* window, std::list<Entity>* entities);

	static bool IsOffScreen(const Entity& e);
};

