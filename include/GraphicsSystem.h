#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class GraphicSystem {
public:
    GraphicSystem(const std::string& name, int width, int height);
    ~GraphicSystem();

    void RenderSmth();
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font;
};
