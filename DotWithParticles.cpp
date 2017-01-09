//
// Created by Vladimir Yarotsky on 1/8/17.
//

#include "DotWithParticles.h"

DotWithParticles::DotWithParticles(int velX, int velY, Texture *m_dotTexture, Texture *p1, Texture *p2, Texture *p3, Texture *shimmer)
        : Dot(velX, velY, m_dotTexture),
          m_p1(p1),
          m_p2(p2),
          m_p3(p3),
          m_shimmer(shimmer) {

    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        m_particles[i] = makeParticle();
    }
}

DotWithParticles::~DotWithParticles() {
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        delete m_particles[i];
    }
}

void DotWithParticles::Render() {
    Dot::Render();
    for (int i = 0; i < TOTAL_PARTICLES; ++i) {
        if (m_particles[i]->IsDead()) {
            delete m_particles[i];
            m_particles[i] = makeParticle();
        }
        m_particles[i]->Render();
    }
}

Particle *DotWithParticles::makeParticle() {
    Texture *texture = nullptr;
    switch(rand() % 3) {
        case 0: texture = m_p1; break;
        case 1: texture = m_p2; break;
        case 2: texture = m_p3; break;
    }
    return new Particle(GetBox().x, GetBox().y, texture, m_shimmer);
}
