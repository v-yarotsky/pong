//
// Created by Vladimir Yarotsky on 1/2/17.
//

#ifndef SDL1_DOT_H
#define SDL1_DOT_H

#include <SDL.h>
#include "texture.h"
#include "constants.h"

class Dot {
public:
    static const int DOT_WIDTH = 40;
    static const int DOT_HEIGHT = 40;

    static const int DOT_VELOCITY = 10;

    explicit Dot(Texture *dotTexture);
    ~Dot();

    void HandleEvent(SDL_Event &e);
    void Move();
    void Render();

private:
    int m_velX, m_velY;
    Texture *m_dotTexture;
    SDL_Rect m_box;
};


#endif //SDL1_DOT_H
