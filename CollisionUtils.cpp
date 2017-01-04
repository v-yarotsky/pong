//
// Created by Vladimir Yarotsky on 1/2/17.
//

#include "CollisionUtils.h"

bool CollisionUtils::CheckCollision(const SDL_Rect &collider1, const SDL_Rect &collider2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = collider1.x;
    rightA = collider1.x + collider1.w;
    topA = collider1.y;
    bottomA = collider1.y + collider1.h;

    leftB = collider2.x;
    rightB = collider2.x + collider2.w;
    topB = collider2.y;
    bottomB = collider2.y + collider2.h;

    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    return true;
}

