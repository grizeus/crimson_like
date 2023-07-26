#include "../include/GraphicSystem.h"
#include <stdexcept>
#include <iostream>

SDL_Window* GraphicSystem::m_Window = nullptr;
SDL_Renderer* GraphicSystem::m_Renderer = nullptr;
TTF_Font* GraphicSystem::m_Font = nullptr;
bool GraphicSystem::m_IsInit = false;


void GraphicSystem::Init(const std::string& name, int width, int height) {
    if (!m_IsInit) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL failed initialization!\n");
        }
        m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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
    else
        std::cout << "Program is already init" << std::endl;
}

void GraphicSystem::Clear() {
    if (m_IsInit) {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        TTF_CloseFont(m_Font);
    
        m_Renderer = nullptr;
        m_Window = nullptr;
        m_Font = nullptr;

        TTF_Quit();
        SDL_Quit();
    }
}

SDL_Renderer* GraphicSystem::GetRenderer() {
    return m_Renderer;
}

SDL_Window* GraphicSystem::GetWindow() {
    return m_Window;
}
TTF_Font* GraphicSystem::GetFont() {
    return m_Font;
}
