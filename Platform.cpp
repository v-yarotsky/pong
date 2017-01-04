//
// Created by Vladimir Yarotsky on 1/3/17.
//

#include "Platform.h"

Platform::Platform(Texture *platformTexture) {
    m_platformTexture = platformTexture;

    m_velY = 0;

    m_box = { 0, 0, PLATFORM_WIDTH, PLATFORM_HEIGHT };
}

Platform::~Platform() {
}

void Platform::HandleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_a: m_velY -= PLATFORM_VELOCITY; break;
            case SDLK_d: m_velY += PLATFORM_VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_a: m_velY += PLATFORM_VELOCITY; break;
            case SDLK_d: m_velY -= PLATFORM_VELOCITY; break;
        }
    }
}

void Platform::Move() {
    m_box.y += m_velY;
    if (m_box.y < 0 || (m_box.y + PLATFORM_HEIGHT > SCREEN_HEIGHT)) {
        m_box.y -= m_velY;
    }
}

void Platform::Render() {
    m_platformTexture->Render(m_box.x, m_box.y);
}
