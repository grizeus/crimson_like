#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Texture.h"
#include "Orientation.h"

class GraphicSystem {
public:
    GraphicSystem() = delete;
    GraphicSystem(GraphicSystem&) = delete;
    void operator=(GraphicSystem&) = delete;
    static void Init(const std::string& name, int width, int height);
    static void Clear();
    
    static SDL_Renderer* GetRenderer();
    static SDL_Window* GetWindow();
    static TTF_Font* GetFont();
private:
    static SDL_Window* m_Window;
    static SDL_Renderer* m_Renderer;
    static TTF_Font* m_Font;
    static bool m_IsInit;
};
