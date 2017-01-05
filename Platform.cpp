//
// Created by Vladimir Yarotsky on 1/3/17.
//

#include "Platform.h"

Platform::Platform(PlatformPosition position, Texture *platformTexture) {
    m_platformTexture = platformTexture;

    m_velY = 0;

    int x;
    switch(position) {
        case PLATFORM_LEFT:  x = 0; break;
        case PLATFORM_RIGHT: x = SCREEN_WIDTH - PLATFORM_WIDTH; break;
    }

    m_box = { x, 0, PLATFORM_WIDTH, PLATFORM_HEIGHT };
}

Platform::Platform(Texture *platformTexture)
        : Platform(PLATFORM_LEFT, platformTexture) {
}

Platform::~Platform() {
}

void Platform::HandleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_k: m_velY -= PLATFORM_VELOCITY; break;
            case SDLK_j: m_velY += PLATFORM_VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_k: m_velY += PLATFORM_VELOCITY; break;
            case SDLK_j: m_velY -= PLATFORM_VELOCITY; break;
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

SDL_Rect Platform::GetBox() const {
    return m_box;
}
