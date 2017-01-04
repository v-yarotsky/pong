//
// Created by Vladimir Yarotsky on 1/3/17.
//

#ifndef PONG_PLATFORM_H
#define PONG_PLATFORM_H

#include <SDL.h>
#include "texture.h"
#include "constants.h"

class Platform {

public:
    static const int PLATFORM_WIDTH = 40;
    static const int PLATFORM_HEIGHT = 160;

    static const int PLATFORM_VELOCITY = 5;

    explicit Platform(Texture *platformTexture);
    ~Platform();

    void HandleEvent(SDL_Event &e);
    void Move();
    void Render();

private:
    int m_velY;
    Texture *m_platformTexture;
    SDL_Rect m_box;
};


#endif //PONG_PLATFORM_H
