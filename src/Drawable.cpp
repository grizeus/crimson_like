#include "../include/Drawable.h"
#include <stdexcept>

Drawable::Drawable(ToolsPtr drawer, Position pos, int w, int h)
    : m_Drawer(drawer)
    , m_Position(pos)
    , m_Width(w)
    , m_Height(h)
{}

Drawable::~Drawable()
{}

void Drawable::Draw()
{
    SDL_Renderer* renderer = m_Drawer->m_Renderer;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
    if (surface == nullptr) 
        throw std::runtime_error(SDL_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) 
        throw std::runtime_error(SDL_GetError());
    SDL_Rect rect = { static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), m_Width, m_Height };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
