#include "Entity.h"

Entity::Entity(int type) {
	Type = type;
	mVelocity = GetVelocity(Type);
	EntityModel.h = 32;
	EntityModel.w = 32;

	EntityCollider = Collider(EntityModel);
}
Entity::~Entity() {}

int Entity::GetVelocity(int type)
{
	switch (type) {
		// Clock & score object
	case 0:
	case 3:
		return -5;
		// Slow enemy
	case 1:
		return -2;
		// Fast enemy
	case 2:
		return -7;
	}
}

void Entity::Init(int spawnY, SDL_Window* window) {
	// Get renderer
	SDL_Renderer* ren = SDL_GetRenderer(window);

	int spawnX;
	SDL_GetWindowSize(window, &spawnX, NULL);

	EntityModel.x = spawnX;
	EntityModel.y = spawnY;

	switch (Type) {
	case 0:
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		break;
	case 1:
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		break;
	case 2:
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		break;
	case 3:
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		break;
	}

	SDL_RenderDrawRect(ren, &EntityModel);
	SDL_RenderFillRect(ren, &EntityModel);
}

void Entity::Update(float deltaTime, Collider playerCollider) {

	// Move entity across screen
	EntityModel.x += mVelocity;

	if (EntityModel.x <= 0) {
		this->~Entity();
	}

	EntityCollider.Update(EntityModel);
}

void Entity::Draw(SDL_Renderer* ren) {

	switch (Type) {
	case 0:
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		break;
	case 1:
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		break;
	case 2:
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		break;
	case 3:
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		break;
	}
	
	SDL_RenderDrawRect(ren, &EntityModel);
	SDL_RenderFillRect(ren, &EntityModel);
}

bool Entity::IsOffScreen(const Entity& e)
{
	return e.EntityModel.x < -32;
}