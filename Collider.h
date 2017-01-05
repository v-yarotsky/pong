//
// Created by Vladimir Yarotsky on 1/4/17.
//

#ifndef PONG_COLLIDER_H
#define PONG_COLLIDER_H

#include <SDL.h>

class Collider {
public:
    virtual SDL_Rect GetBox() const = 0;
};

#endif //PONG_COLLIDER_H
