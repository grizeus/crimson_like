#include "../include/TextureManager.h"
#include <stdexcept>

TextureManager::TextureManager()
{}


void TextureManager::LoadFromFile(SDL_Renderer* renderer, Texture& texture, const std::string& path, int width, int height) {
    texture.Destroy();
    SDL_Texture* new_texture = texture.GetTexture();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) 
        throw std::runtime_error("Failed to load image: " + path + " " + IMG_GetError());
    else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + path + " " + SDL_GetError());
        else {
            width = surface->w;
            height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    texture.SetTexture(new_texture); 
}

void TextureManager::LoadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, Texture& texture, const std::string& text, const SDL_Color& color, int width, int height) {
    texture.Destroy();
    SDL_Texture* new_texture = texture.GetTexture();
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
        throw std::runtime_error("Failed to render text surface: " + text + " " + TTF_GetError());
    else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + text + " " + SDL_GetError());
        else {
            width = surface->w;
            height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    texture.SetTexture(new_texture);
}
