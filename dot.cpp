//
// Created by Vladimir Yarotsky on 1/2/17.
//

#include "dot.h"

Dot::Dot(Texture *dotTexture) {
    m_dotTexture = dotTexture;

    m_velX = 0;
    m_velY = 0;

    m_box = { 0, 0, DOT_WIDTH, DOT_HEIGHT };
}

Dot::~Dot() {
}

void Dot::HandleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w: m_velY -= DOT_VELOCITY; break;
            case SDLK_s: m_velY += DOT_VELOCITY; break;
            case SDLK_a: m_velX -= DOT_VELOCITY; break;
            case SDLK_d: m_velX += DOT_VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w: m_velY += DOT_VELOCITY; break;
            case SDLK_s: m_velY -= DOT_VELOCITY; break;
            case SDLK_a: m_velX += DOT_VELOCITY; break;
            case SDLK_d: m_velX -= DOT_VELOCITY; break;
        }
    }
}

void Dot::Move() {
    m_box.x += m_velX;
    if (m_box.x < 0 || (m_box.x + DOT_WIDTH > SCREEN_WIDTH)) {
        m_box.x -= m_velX;
    }

    m_box.y += m_velY;
    if (m_box.y < 0 || (m_box.y + DOT_HEIGHT > SCREEN_HEIGHT)) {
        m_box.y -= m_velY;
    }
}

void Dot::Render() {
    m_dotTexture->Render(m_box.x, m_box.y);
}
