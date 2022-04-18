#include "Player.h"
#include <iostream>

Player::Player() {
	mPlayerModel.x = 32;
	mPlayerModel.y = 32;
	mPlayerModel.h = 32;
	mPlayerModel.w = 32;
	
	PlayerCollider = Collider(&mPlayerModel);

	mVelocity = 0;
	mGravity = 40;
}

Player::~Player() {}

void Player::Init(SDL_Renderer  *ren) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);

	SDL_RenderDrawRect(ren, &mPlayerModel);
	SDL_RenderFillRect(ren, &mPlayerModel);
}

void Player::Fly(float deltaTime) {
	mVelocity = -80;
}

void Player::Update(float deltaTime) {

	// Apply gravity
	mPlayerModel.y += (mGravity + mVelocity) * deltaTime;

	// Slow down velocity
	if (mVelocity < 0) {
		mVelocity += 2;
	}
}

void Player::Draw(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_RenderDrawRect(ren, &mPlayerModel);
	SDL_RenderFillRect(ren, &mPlayerModel);
}