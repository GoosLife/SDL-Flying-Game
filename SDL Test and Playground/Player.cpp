#include "Player.h"

Player::Player() {
	PlayerModel.x = 32;
	PlayerModel.y = 32;
	PlayerModel.h = 32;
	PlayerModel.w = 32;
	
	PlayerCollider = Collider(PlayerModel);

	mVelocity = 0;
	mGravity = 40;
}

Player::~Player() {}

void Player::Init(SDL_Renderer  *ren) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);

	SDL_RenderDrawRect(ren, &PlayerModel);
	SDL_RenderFillRect(ren, &PlayerModel);
}

void Player::Fly(float deltaTime) {
	mVelocity = -80;
}

void Player::Update(float deltaTime) {

	// Apply gravity
	PlayerModel.y += (mGravity + mVelocity) * deltaTime;

	// Slow down velocity
	if (mVelocity < 0) {
		mVelocity += 2;
	}

	PlayerCollider.Update(PlayerModel);
}

void Player::Draw(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_RenderDrawRect(ren, &PlayerModel);
	SDL_RenderFillRect(ren, &PlayerModel);
}