#include "Entity.h"
#include <iostream> // DEBUG

Entity::Entity(int type) {
	mType = type;
	mVelocity = -5;
	EntityModel.h = 32;
	EntityModel.w = 32;

	EntityCollider = Collider(&EntityModel);
}
Entity::~Entity() {}

void Entity::Init(int spawnY, SDL_Window* window) {
	// Get renderer
	SDL_Renderer* ren = SDL_GetRenderer(window);

	int spawnX;
	SDL_GetWindowSize(window, &spawnX, NULL);

	EntityModel.x = spawnX;
	EntityModel.y = spawnY;

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	SDL_RenderDrawRect(ren, &EntityModel);
	SDL_RenderFillRect(ren, &EntityModel);
}

void Entity::Update(float deltaTime, Player player) {

	// Move entity across screen
	EntityModel.x += mVelocity;

	if (EntityModel.x <= 0) {
		this->~Entity();
	}

	if (EntityCollider.HasCollided(&player.PlayerCollider) == true) {
		std::cout << "I detected it from the update function." << std::endl;
	}
}

void Entity::Draw(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderDrawRect(ren, &EntityModel);
	SDL_RenderFillRect(ren, &EntityModel);
}