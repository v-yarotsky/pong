//
// Created by Vladimir Yarotsky on 1/2/17.
//

#ifndef SDL1_TEXTURE_H
#define SDL1_TEXTURE_H

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
#include <exception>
#include <string>

class TextureLoadException : public std::exception {
public:
    TextureLoadException(std::string path, std::string errMsg = "");
    virtual const char* what() const throw();

private:
    std::string m_path;
    std::string m_err;
};

class Texture {
public:
    Texture(SDL_Renderer *renderer, std::string path, bool colorKey = false);
    Texture(std::string text, SDL_Renderer *renderer, TTF_Font* font, SDL_Color textColor);
    ~Texture();

    void Render(int x, int y, SDL_Rect *clip = nullptr);
    void SetBlendMode(SDL_BlendMode blending);
    void SetAlpha(Uint8 alpha);
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    int Width() const;
    int Height() const;

private:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    int m_width;
    int m_height;
};

#endif //SDL1_TEXTURE_H
