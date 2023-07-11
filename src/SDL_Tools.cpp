#include "../include/SDL_Tools.h"

bool SDL_Tools::ToolsInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error("SDL failed initialization!\n");
       return false;
    }
    if (SDL_CreateWindowAndRenderer(m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN , &m_Window, &m_Renderer) != 0) {
        throw std::runtime_error(SDL_GetError());
        return false;
    }
    SDL_SetWindowTitle(m_Window, "Crimson Game");
    SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // if (TTF_Init() == -1) {
    //     throw std::runtime_error(TTF_GetError());
    //     return false;
    // }
    //
 //    m_Font = TTF_OpenFont("../media/mononoki-Bold.ttf", 72);
	// if (m_Font == NULL) {
 //        throw std::runtime_error(TTF_GetError());
 //        return false;
 //    }
    return true;
}

void SDL_Tools::ToolsQuit()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    // TTF_CloseFont(m_Font);

    m_Renderer = nullptr;
    m_Window = nullptr;
    // m_Font = nullptr;

    // TTF_Quit();
    SDL_Quit();
}

SDL_Tools::~SDL_Tools() { ToolsQuit(); }
