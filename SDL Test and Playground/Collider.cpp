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

            hasCollided = true;

            return true;
        }
        return false;
    }
    return false;
}
