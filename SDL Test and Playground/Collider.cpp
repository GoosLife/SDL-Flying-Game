#include "Collider.h"

Collider::Collider(SDL_Rect& rect) {
    colliderBody = rect;
    minX = colliderBody.x;
    maxX = minX + colliderBody.w;
    minY = colliderBody.y;
    maxY = minY + colliderBody.h;

    hasCollided = false;
}

Collider::Collider(SDL_Rect& rect, std::string name) {
    colliderBody = rect;
    minX = colliderBody.x;
    maxX = minX + colliderBody.w;
    minY = colliderBody.y;
    maxY = minY + colliderBody.h;

    Name = name;

    hasCollided = false;
}

Collider::~Collider() {}

void Collider::Update(SDL_Rect& rect) {
    colliderBody = rect;
    minX = colliderBody.x;
    maxX = minX + colliderBody.w;
    minY = colliderBody.y;
    maxY = minY + colliderBody.h;
}

bool Collider::HasCollided(Collider* other)
{
    if (!hasCollided) {
        if (minX < other->maxX &&
            maxX > other->minX &&
            minY < other->maxY &&
            maxY > other->minY) {

            std::cout << "Min x = " << colliderBody.x << "\n";
            std::cout << "Player min x = " << other->colliderBody.x << "\n";
            std::cout << "Max x = " << colliderBody.x + colliderBody.w << "\n";
            std::cout << "Player max x = " << other->colliderBody.x + other->colliderBody.w << "\n";
            std::cout << "Min y = " << colliderBody.y << "\n";
            std::cout << "Player min y = " << other->colliderBody.y << "\n";
            std::cout << "Max y = " << colliderBody.y + colliderBody.h << "\n";
            std::cout << "Player max y = " << other->colliderBody.y + other->colliderBody.h << "\n";

            hasCollided = true;

            return true;
        }
        return false;
    }
    return false;
}
