#pragma once
#include "SDL_Tools.h"
#include <string>

class Texture {
public:
    Texture(ToolsPtr);
    ~Texture();
    
    void Free();
    // void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // inline int GetWidth() const { return m_Width; }
    // inline int GetHeight() const { return m_Height; }
private:
    SDL_Texture* m_Texture;
};
