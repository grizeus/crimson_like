#pragma once
#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    void LoadFromFile(SDL_Renderer* renderer, Texture* texture, const std::string& path, int width, int height);
    void LoadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, Texture* texture, const std::string& path, const SDL_Color& color);
};
