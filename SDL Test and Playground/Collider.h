#pragma once
#include <iostream>
#include <string>
#include "SDL.h"

class Collider
{
	SDL_Rect* colliderBody;
	int minX;
	int maxX;
	int minY;
	int maxY;

public:
	Collider(SDL_Rect* rect);
	Collider(SDL_Rect* rect, std::string name);
	~Collider();

	std::string Name;

	bool HasCollided(Collider* other);
};

