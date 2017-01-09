//
// Created by Vladimir Yarotsky on 1/8/17.
//

#ifndef PONG_PARTICLE_H
#define PONG_PARTICLE_H

#include "texture.h"

class Particle {
public:
    Particle(int x, int y, Texture *texture, Texture *shimmer);
    void Render();
    bool IsDead();

private:
    int m_posX, m_posY;
    int m_frame;
    Texture *m_texture;
    Texture *m_shimmer;
};


#endif //PONG_PARTICLE_H
