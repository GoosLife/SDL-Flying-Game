#pragma once
#include "SDL.h"
#include "Collider.h"

class Player {

private:

	float mVelocity;
	float mGravity;

public:

	SDL_Rect PlayerModel;

	Player();
	~Player();

	Collider PlayerCollider = Collider(PlayerModel, "Player");

	void Init(SDL_Renderer* ren);
	void Draw(SDL_Renderer* ren);
	void Fly(float time);
	void Update(float time);

};