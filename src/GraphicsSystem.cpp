#include "../include/GraphicsSystem.h"
#include <SDL2/SDL_render.h>
#include <stdexcept>

GraphicsSystem::GraphicsSystem(const std::string& name, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error("SDL failed initialization!\n");
    }
    m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (m_Window == nullptr)
        throw std::runtime_error(SDL_GetError());
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr)
        throw std::runtime_error(SDL_GetError());

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

void GraphicsSystem::RenderTexture(Texture& texture, Position position, int width, int height) {
    SDL_Rect rect = { position.x, position.y, width, height };
    SDL_RenderCopy(m_Renderer, texture.GetTexture(), nullptr, &rect);
}

void GraphicsSystem::RenderEnemy(Position position, int width, int height) {
    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect EnemyRect = { position.x, position.y, width, height };
    SDL_RenderFillRect(m_Renderer, &EnemyRect);
}
