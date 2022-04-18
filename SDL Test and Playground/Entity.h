#pragma once
#include "SDL.h"
#include "Collider.h"
#include "Player.h"

class Entity
{
private:

	int mType;
	float mVelocity;

public:
	SDL_Rect EntityModel;

	Collider EntityCollider = Collider(&EntityModel);

	Entity(int type);
	~Entity();

	void Init(int spawnY, SDL_Window* window);
	void Update(float deltaTime, Player player);
	void Draw(SDL_Renderer* ren);
};
