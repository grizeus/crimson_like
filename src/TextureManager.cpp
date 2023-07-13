#include "../include/TextureManager.h"
#include <stdexcept>

TextureManager::TextureManager()
    : m_Texture(nullptr)
{}

void TextureManager::Free() {
    if (m_Texture != nullptr) {
        m_Texture->Destroy();
        m_Texture = nullptr;
    }
}

void TextureManager::LoadFromFile(GraphicsSystem graphic, const std::string& path, int width, int height) {
    Free();
    auto texture = m_Texture->GetTexture();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) 
        throw std::runtime_error("Failed to load image: " + path + " " + IMG_GetError());
    else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(graphic.GetRenderer(), surface);
        if (texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + path + " " + SDL_GetError());
        else {
            width = surface->w;
            height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    m_Texture->SetTexture(texture);
}

void TextureManager::LoadFromRenderedText(GraphicsSystem graphic, const std::string& text, const SDL_Color& color, int width, int height) {
    Free();
    auto texture = m_Texture->GetTexture();
    SDL_Surface* surface = TTF_RenderText_Solid(graphic.GetFont(), text.c_str(), color);
    if (surface == nullptr)
        throw std::runtime_error("Failed to render text surface: " + text + " " + TTF_GetError());
    else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(graphic.GetRenderer(), surface);
        if (texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + text + " " + SDL_GetError());
        else {
            width = surface->w;
            height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    m_Texture->SetTexture(texture);
}
