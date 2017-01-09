//
// Created by Vladimir Yarotsky on 1/3/17.
//

#ifndef PONG_PLATFORM_H
#define PONG_PLATFORM_H

#include <SDL.h>
#include "texture.h"
#include "Collider.h"
#include "constants.h"
#include "TextureMap.h"

enum PlatformPosition {
    PLATFORM_LEFT,
    PLATFORM_RIGHT
};

class Platform : public Collider {

public:
    static const int PLATFORM_WIDTH = 40;
    static const int PLATFORM_HEIGHT = 160;

    static const int PLATFORM_VELOCITY = 8;

    explicit Platform(TextureMap &textureMap);
    Platform(PlatformPosition position, TextureMap &textureMap);
    ~Platform();

    void HandleEvent(SDL_Event &e);
    void Move();
    void Render();

    SDL_Rect GetBox() const override;
private:
    int m_velY;
    Texture *m_platformTexture;
    SDL_Rect m_box;
};


#endif //PONG_PLATFORM_H
