//
// Created by Vladimir Yarotsky on 1/2/17.
//

#ifndef SDL1_COLLISIONUTILS_H
#define SDL1_COLLISIONUTILS_H

#include <SDL.h>
#include "constants.h"

class CollisionUtils {
public:
    static bool CheckCollision(const SDL_Rect &collider1, const SDL_Rect &collider2);
};


#endif //SDL1_COLLISIONUTILS_H
