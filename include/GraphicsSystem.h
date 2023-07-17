#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Texture.h"
#include "Orientation.h"

class GraphicsSystem {
public:
    GraphicsSystem(const std::string& name, int width, int height);
    ~GraphicsSystem();

    void RenderTexture(Texture& texture, Position position, int width, int height);
    void RenderEnemy(Position position, int width, int height);

    inline SDL_Renderer* GetRenderer() const { return m_Renderer; }
    inline TTF_Font* GetFont() const { return m_Font; }
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font;
};
