//
// Created by Vladimir Yarotsky on 1/2/17.
//

#include <sstream>
#include <iostream>
#include "texture.h"

TextureLoadException::TextureLoadException(std::string path, std::string errMsg)
        : exception() {
    m_path = path;
    m_err = errMsg;
}

const char* TextureLoadException::what() const throw() {
    return ("Failed to load texture " + m_path + ": " + m_err).c_str();
}



Texture::Texture(SDL_Renderer *renderer, std::string path, bool colorKey) {
    SDL_Texture *newTexture;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throw TextureLoadException(path, IMG_GetError());
    }

    if (colorKey) {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
        throw TextureLoadException(path, SDL_GetError());
    }

    m_renderer = renderer;
    m_texture = newTexture;
    m_width = loadedSurface->w;
    m_height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
}

Texture::Texture(std::string text, SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        throw TextureLoadException(text, TTF_GetError());
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (newTexture == nullptr) {
        throw TextureLoadException(text, SDL_GetError());
    }

    m_renderer = renderer;
    m_width = textSurface->w;
    m_height = textSurface->h;

    m_texture = newTexture;
    SDL_FreeSurface(textSurface);
}

Texture::~Texture() {
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
    }
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
}

void Texture::Render(int x, int y, SDL_Rect *clip) {
    SDL_Rect renderQuad = {x, y, m_width, m_height};

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(m_renderer, m_texture, clip, &renderQuad);
}

void Texture::SetBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(m_texture, blending);
}

void Texture::SetAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

int Texture::Width() const {
    return m_width;
}

int Texture::Height() const {
    return m_height;
}

