//
// Created by Vladimir Yarotsky on 1/8/17.
//

#include "DotWithParticles.h"

DotWithParticles::DotWithParticles(int velX, int velY, TextureMap &textureMap)
        : Dot(velX, velY, textureMap),
          m_p1(textureMap["particle_red"]),
          m_p2(textureMap["particle_green"]),
          m_p3(textureMap["particle_blue"]),
          m_shimmer(textureMap["particle_shimmer"]) {

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
