#pragma once
#include <iostream>
#include <string>
#include "SDL.h"

class Collider
{
	SDL_Rect colliderBody;
	int minX;
	int maxX;
	int minY;
	int maxY;

	bool hasCollided;
public:
	Collider(SDL_Rect& rect);
	Collider(SDL_Rect& rect, std::string name);
	~Collider();

	std::string Name;

	void Update(SDL_Rect& rect);

	bool HasCollided(Collider* other);
};

