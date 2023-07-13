#pragma once
#include "GraphicsSystem.h"
#include <string>

class Texture {
public:
    Texture();
    Texture(Texture&);
    ~Texture();

    inline SDL_Texture* GetTexture() const { return m_Texture; }
    inline void SetTexture(SDL_Texture* texture) { m_Texture = texture; }

    void Destroy();
private:
    SDL_Texture* m_Texture;
};
