#pragma once
#include <SDL2/SDL.h> 
#include <string>

class Texture {
public:
    Texture();
    Texture(Texture&);
    ~Texture();

    void Destroy();

    inline SDL_Texture* GetTexture() const { return m_Texture; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline void SetWidth(int width) { m_Width = width; }
    inline void SetHeight(int height) { m_Height = height; }

    void SetTexture(SDL_Texture* texture); 
private:
    SDL_Texture* m_Texture;
    int m_Width;
    int m_Height;
};
