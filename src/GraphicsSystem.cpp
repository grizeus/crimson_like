#include "../include/GraphicsSystem.h"
#include <stdexcept>

GraphicsSystem::GraphicsSystem(const std::string& name, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
       throw std::runtime_error("SDL failed initialization!\n");
    }
    else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }
    m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (m_Window == nullptr)
        throw std::runtime_error(SDL_GetError());
    else {
        m_GLContext = SDL_GL_CreateContext(m_Window);
        if (!m_GLContext)
            throw std::runtime_error(SDL_GetError());
        else {
            if (gl3wInit())
                throw std::runtime_error("gl3w failed initialization!\n");
            if (!gl3wIsSupported(3, 2)) 
                throw std::runtime_error("OpenGL 3.2 not supported!\n");
            printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
        }
    }
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
    SDL_GL_DeleteContext(m_GLContext);
    
    m_Renderer = nullptr;
    m_Window = nullptr;
    m_Font = nullptr;
    m_GLContext = nullptr;

    TTF_Quit();
    SDL_Quit();
}

void GraphicsSystem::RenderTexture(Texture& texture, Position position, int width, int height) {
    SDL_Rect rect = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
    SDL_RenderCopy(m_Renderer, texture.GetTexture(), nullptr, &rect);
}

void GraphicsSystem::RenderEnemy(Position position, int width, int height) {
    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect EnemyRect = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
    SDL_RenderFillRect(m_Renderer, &EnemyRect);
}

void GraphicsSystem::RenderBullet(Position position, int width, int height) {
    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect BulletRect = { static_cast<int>(position.x), static_cast<int>(position.y), width, height };
    SDL_RenderFillRect(m_Renderer, &BulletRect);
}
