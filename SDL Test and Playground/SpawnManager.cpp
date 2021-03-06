#include "SpawnManager.h"

SpawnManager::SpawnManager() {}
SpawnManager::~SpawnManager() {}

void SpawnManager::SpawnEntity(SDL_Window* window, std::list<Entity>* entities) {
	// Get window size
	int windowHeight;
	SDL_GetWindowSize(window, NULL, &windowHeight);

	// Create random seed
	srand(time(NULL));

	int spawnId = rand() % 4 + 1;

	// Only go if this spawn ID is different from the previous spawn ID
	if (spawnId != mOldResult) {
		int spawnY = rand() % windowHeight + 1;

		switch (spawnId) {
		case 1:
			SpawnClock(spawnY, window, entities);
			break;
		case 2:
			SpawnScoreObject(spawnY, window, entities);
			break;
		case 3:
			SpawnSlowEnemy(spawnY, window, entities);
			break;
		case 4:
			SpawnFastEnemy(spawnY, window, entities);
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			break;
		}
	}

	// keep track of this result
	mOldResult = spawnId;
}

void SpawnManager::SpawnClock(int spawnY, SDL_Window* window, std::list<Entity>* entities) {
	Entity c(0);
	c.Init(spawnY, window);
	entities->push_back(c);
}

void SpawnManager::SpawnSlowEnemy(int spawnY, SDL_Window* window, std::list<Entity>* entities) {
	Entity c(1);
	c.Init(spawnY, window);
	entities->push_back(c);
}

void SpawnManager::SpawnFastEnemy(int spawnY, SDL_Window* window, std::list<Entity>* entities) {
	Entity c(2);
	c.Init(spawnY, window);
	entities->push_back(c);
}

void SpawnManager::SpawnScoreObject(int spawnY, SDL_Window* window, std::list<Entity>* entities) {
	Entity c(3);
	c.Init(spawnY, window);
	entities->push_back(c);
}


