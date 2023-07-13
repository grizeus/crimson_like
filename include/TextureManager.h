#pragma once
#include "GraphicsSystem.h"
#include "Texture.h"
#include <SDL2/SDL_image.h>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    void Free();
    void LoadFromFile(GraphicsSystem, const std::string&, int, int);
    void LoadFromRenderedText(GraphicsSystem, const std::string&, const SDL_Color&, int, int);
private:
    Texture* m_Texture;
};
