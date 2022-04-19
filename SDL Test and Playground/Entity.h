#pragma once
#include "SDL.h"
#include "Collider.h"
#include "Player.h"

class Entity
{
private:

	float mVelocity;

public:
	int Type;

	SDL_Rect EntityModel;

	Collider EntityCollider = Collider(EntityModel);

	Entity(int type);
	~Entity();

	int GetVelocity(int type);

	void Init(int spawnY, SDL_Window* window);
	void Update(float deltaTime, Collider playerCollider);
	void Draw(SDL_Renderer* ren);

	static bool IsOffScreen(const Entity& e);
};
