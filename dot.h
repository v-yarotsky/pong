//
// Created by Vladimir Yarotsky on 1/2/17.
//

#ifndef SDL1_DOT_H
#define SDL1_DOT_H

#include <SDL.h>
#include "texture.h"
#include "constants.h"
#include "Collider.h"
#include "Platform.h"
#include "TextureMap.h"

class Dot : public Collider {
public:
    static const int DOT_WIDTH = 40;
    static const int DOT_HEIGHT = 40;

    static const int DOT_VELOCITY = 10;

    explicit Dot(TextureMap &textureMap);
    Dot(int velX, int velY, TextureMap &textureMap);
    ~Dot();

    void HandleEvent(SDL_Event &e);
    void Move(const Platform &platform);
    void Render();
    void Reset(int velX, int velY);

    SDL_Rect GetBox() const override;

private:
    int m_velX, m_velY;
    Texture *m_dotTexture;
    SDL_Rect m_box;
};


#endif //SDL1_DOT_H
