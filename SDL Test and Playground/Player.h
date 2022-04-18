#pragma once
#include "SDL.h"
#include "Collider.h"

class Player {

private:

	SDL_Rect mPlayerModel;
	float mVelocity;
	float mGravity;

public:

	Player();
	~Player();

	Collider PlayerCollider = Collider(&mPlayerModel, "Player");

	void Init(SDL_Renderer* ren);
	void Draw(SDL_Renderer* ren);
	void Fly(float time);
	void Update(float time);

};