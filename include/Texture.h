#pragma once
#include "SDL_Tools.h"
#include <string>

class Texture {
public:
    Texture(ToolsPtr);
    ~Texture();
    void LoadFromFile(const std::string& path);
    void LoadFromRenderedText(const std::string& text, const SDL_Color& color);
    void Free();
    void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
private:
    ToolsPtr m_Drawer;
    SDL_Texture* m_Texture;
    int m_Width;
    int m_Height;
};
