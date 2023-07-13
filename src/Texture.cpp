#include "../include/Texture.h"
#include <stdexcept>

Texture::Texture(ToolsPtr drawer)
    : m_Texture(nullptr)
    , m_Width(0)
    , m_Height(0)
    , m_Drawer(drawer)
{}

Texture::~Texture() {
    Free();
}

void Texture::Free() {
    if (m_Texture != nullptr) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
        m_Width = 0;
        m_Height = 0;
    }
}

void Texture::LoadFromFile(const std::string& path) {
    Free();
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) 
        throw std::runtime_error("Failed to load image: " + path + " " + IMG_GetError());
    else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(m_Drawer->m_Renderer, surface);
        if (texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + path + " " + SDL_GetError());
        else {
            m_Width = surface->w;
            m_Height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    SDL_FreeSurface(surface);
}

void Texture::LoadFromRenderedText(const std::string& text, const SDL_Color& color) {
    Free();
    SDL_Surface* surface = TTF_RenderText_Solid(m_Drawer->m_Font, text.c_str(), color);
    if (surface == nullptr)
        throw std::runtime_error("Failed to render text surface: " + text + " " + TTF_GetError());
    else {
        m_Texture = SDL_CreateTextureFromSurface(m_Drawer->m_Renderer, surface);
        if (m_Texture == nullptr) 
            throw std::runtime_error("Failed to create texture from surface: " + text + " " + SDL_GetError());
        else {
            m_Width = surface->w;
            m_Height = surface->h;
        }
        SDL_FreeSurface(surface);
    }
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderRect = { x, y, m_Width, m_Height };
    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopyEx(m_Drawer->m_Renderer, m_Texture, clip, &renderRect, angle, center, flip);
}
