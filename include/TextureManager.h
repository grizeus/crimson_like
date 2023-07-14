#pragma once
#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    void LoadFromFile(SDL_Renderer*, Texture&, const std::string&, int, int);
    void LoadFromRenderedText(SDL_Renderer*, TTF_Font*, Texture&, const std::string&, const SDL_Color&, int, int);
};
