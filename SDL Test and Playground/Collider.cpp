#include "Collider.h"

Collider::Collider(SDL_Rect* rect) {
    colliderBody = rect;
    minX = colliderBody->x;
    maxX = minX + colliderBody->w;
    minY = colliderBody->y;
    maxY = minY + colliderBody->y;
}

Collider::Collider(SDL_Rect* rect, std::string name) {
    colliderBody = rect;
    minX = colliderBody->x;
    maxX = minX + colliderBody->w;
    minY = colliderBody->y;
    maxY = minY + colliderBody->y;

    Name = name;
}

Collider::~Collider() {}

bool Collider::HasCollided(Collider* other)
{
    if (minX < other->maxX &&
        maxX > other->minX &&
        minY < other->maxY &&
        maxY > other->minY) {
        std::cout << "Collision detected!" << std::endl;
        return true;
    }
}
