//
// Created by Vladimir Yarotsky on 1/8/17.
//

#include "Particle.h"

Particle::Particle(int x, int y, Texture *texture, Texture *shimmer)
        : m_texture(texture),
          m_shimmer(shimmer) {
    m_posX = x - 5 + (rand() % 25);
    m_posY = y - 5 + (rand() % 25);

    m_frame = rand() % 5;
}

void Particle::Render() {
    m_texture->Render(m_posX, m_posY);

    if (m_frame % 2 == 0) {
        m_shimmer->Render(m_posX, m_posY);
    }

    m_frame++;
}

bool Particle::IsDead() {
    return m_frame > 10;
}
