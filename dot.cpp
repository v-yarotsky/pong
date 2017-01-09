//
// Created by Vladimir Yarotsky on 1/2/17.
//

#include "dot.h"
#include "CollisionUtils.h"

Dot::Dot(TextureMap &textureMap)
        : Dot(0, 0, textureMap) {
}

Dot::Dot(int velX, int velY, TextureMap &textureMap) {
    m_dotTexture = textureMap["dot"];

    m_velX = velX;
    m_velY = velY;

    m_box = { 0, 0, DOT_WIDTH, DOT_HEIGHT };
}

Dot::~Dot() {
}

void Dot::HandleEvent(SDL_Event &e) {
}

void Dot::Move(const Platform &platform) {
    m_box.x += m_velX;
    if (m_box.x < 0 || CollisionUtils::CheckCollision(GetBox(), platform.GetBox())) {
        m_box.x -= m_velX;
        m_velX *= -1;
    }

    m_box.y += m_velY;
    if (m_box.y < 0 || (m_box.y + DOT_HEIGHT > SCREEN_HEIGHT) || CollisionUtils::CheckCollision(GetBox(), platform.GetBox())) {
        m_box.y -= m_velY;
        m_velY *= -1;
    }
}

void Dot::Render() {
    m_dotTexture->Render(m_box.x, m_box.y);
}

void Dot::Reset(int velX, int velY) {
    m_velX = velX;
    m_velY = velY;

    m_box = { 0, 0, DOT_WIDTH, DOT_HEIGHT };
}

SDL_Rect Dot::GetBox() const {
    return m_box;
}
