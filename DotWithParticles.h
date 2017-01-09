//
// Created by Vladimir Yarotsky on 1/8/17.
//

#ifndef PONG_DOTWITHPARTICLES_H
#define PONG_DOTWITHPARTICLES_H

#include "dot.h"
#include "texture.h"
#include "Particle.h"

class DotWithParticles : public Dot {
public:
    DotWithParticles(int velX, int velY, Texture *m_dotTexture, Texture *p1, Texture *p2, Texture *p3, Texture *shimmer);
    ~DotWithParticles();

    void Render();
private:
    Particle *makeParticle();

    Particle *m_particles[TOTAL_PARTICLES];
    Texture *m_p1, *m_p2, *m_p3, *m_shimmer;
};


#endif //PONG_DOTWITHPARTICLES_H
