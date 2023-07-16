#include "../include/TextureManager.h"
#include <stdexcept>

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

void TextureManager::LoadFromFile(SDL_Renderer* renderer, Texture* texture, const std::string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) 
        throw std::runtime_error("Failed to load image: " + path + " " + IMG_GetError());
    else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + path + " " + SDL_GetError());
        else {
            texture->SetWidth(surface->w);
            texture->SetHeight(surface->h);
        }
        SDL_FreeSurface(surface);
    }
    texture->SetTexture(newTexture); 
}

void TextureManager::LoadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, Texture* texture, const std::string& text, const SDL_Color& color) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
        throw std::runtime_error("Failed to render text surface: " + text + " " + TTF_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + text + " " + SDL_GetError());
        else {
            texture->SetWidth(surface->w);
            texture->SetHeight(surface->h);
        }
        SDL_FreeSurface(surface);
    }
    texture->SetTexture(newTexture);
}
