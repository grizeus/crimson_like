#include "../include/GraphicsSystem.h"
#include <SDL2/SDL_render.h>
#include <stdexcept>

GraphicsSystem::GraphicsSystem(const std::string& name, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error("SDL failed initialization!\n");
    }
    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN , &m_Window, &m_Renderer) != 0) 
        throw std::runtime_error(SDL_GetError());
    
    SDL_SetWindowTitle(m_Window, name.c_str());
    SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        throw std::runtime_error(IMG_GetError());
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error(TTF_GetError());
    }

    m_Font = TTF_OpenFont("../media/mononoki-Bold.ttf", 18);
    if (m_Font == NULL) 
        throw std::runtime_error(TTF_GetError());
}

GraphicsSystem::~GraphicsSystem() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_CloseFont(m_Font);

    m_Renderer = nullptr;
    m_Window = nullptr;
    m_Font = nullptr;

    TTF_Quit();
    SDL_Quit();
}

void GraphicsSystem::RenderTexture(Texture& texture, Position pos, int width, int height) {
    SDL_Rect rect = { pos.x, pos.y, width, height };
    SDL_RenderCopy(m_Renderer, texture.GetTexture(), nullptr, &rect);
}

void GraphicsSystem::RenderEnemy(Position pos, int width, int height) {
    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect EnemyRect = { pos.x, pos.y, width, height };
    SDL_RenderFillRect(m_Renderer, &EnemyRect);
}
